#include "baseendpoint.h"
#include "innertube/itc-objects/innertubeauthstore.h"
#include <QEventLoop>
#include <QJsonDocument>
#include <QNetworkReply>

namespace InnertubeEndpoints
{
    namespace EndpointMethods
    {
        QJsonValue getData(const QString& path, const QJsonObject& body,
                           const InnertubeContext* context, const InnertubeAuthStore* authStore)
        {
            static thread_local QNetworkAccessManager* nam = [] {
                QNetworkAccessManager* nam = new QNetworkAccessManager;
                nam->setRedirectPolicy(QNetworkRequest::NoLessSafeRedirectPolicy);
                return nam;
            }();

            QNetworkReply* rep = nam->post(
                prepareRequest(path, context, authStore),
                QJsonDocument(body).toJson(QJsonDocument::Compact));
            QObject::connect(rep, &QNetworkReply::finished, rep, &QObject::deleteLater);

            QEventLoop loop;
            QObject::connect(rep, &QNetworkReply::finished, &loop, &QEventLoop::quit);
            loop.exec();

            return QJsonDocument::fromJson(rep->readAll()).object();
        }

        QNetworkRequest prepareRequest(
            const QString& path, const InnertubeContext* context, const InnertubeAuthStore* authStore)
        {
            QNetworkRequest req(path);
            req.setAttribute(QNetworkRequest::CookieSaveControlAttribute, QNetworkRequest::Manual);

            if (authStore->populated())
            {
                req.setRawHeader("Authorization", authStore->generateSAPISIDHash().toUtf8());
                req.setRawHeader("Cookie", authStore->toCookieString().toUtf8());
                req.setRawHeader("X-Goog-AuthUser", "0");
            }

            req.setRawHeader("Content-Type", "application/json");
            req.setRawHeader("X-Goog-Visitor-Id", context->client.visitorData.toUtf8());
            req.setRawHeader("X-YOUTUBE-CLIENT-NAME", QByteArray::number(static_cast<int>(context->client.clientType)));
            req.setRawHeader("X-YOUTUBE-CLIENT-VERSION", context->client.clientVersion.toLatin1());
            req.setRawHeader("X-ORIGIN", "https://www.youtube.com");

            return req;
        }
    }
}
