#include "baseendpoint.h"
#include "innertube/itc-objects/innertubeauthstore.h"
#include <QEventLoop>
#include <QJsonDocument>
#include <QNetworkReply>

namespace
{
    QNetworkAccessManager* networkAccessManager()
    {
        static thread_local QNetworkAccessManager* nam = [] {
            QNetworkAccessManager* nam = new QNetworkAccessManager;
            nam->setRedirectPolicy(QNetworkRequest::NoLessSafeRedirectPolicy);
            return nam;
        }();
        return nam;
    }
}

namespace InnertubeEndpoints
{
    namespace EndpointMethods
    {
        QFuture<QJsonValue> getData(
            const QString& path, const QJsonObject& body,
            const InnertubeContext* context, const InnertubeAuthStore* authStore)
        {
            QFutureInterface<QJsonValue> futureInterface;
            futureInterface.reportStarted();

            QNetworkReply* rep = networkAccessManager()->post(
                prepareRequest(path, context, authStore),
                QJsonDocument(body).toJson(QJsonDocument::Compact));

            QObject::connect(rep, &QNetworkReply::finished, [futureInterface, rep]() mutable {
                rep->deleteLater();
                futureInterface.reportResult(QJsonDocument::fromJson(rep->readAll()).object());
                futureInterface.reportFinished();
            });

            return futureInterface.future();
        }

        QFuture<void> getPlain(
            const QString& path, const QJsonObject& body,
            const InnertubeContext* context, const InnertubeAuthStore* authStore)
        {
            QFutureInterface<void> futureInterface;
            futureInterface.reportStarted();

            QNetworkReply* rep = networkAccessManager()->post(
                prepareRequest(path, context, authStore),
                QJsonDocument(body).toJson(QJsonDocument::Compact));

            QObject::connect(rep, &QNetworkReply::finished, [futureInterface, rep]() mutable {
                rep->deleteLater();
                futureInterface.reportFinished();
            });

            return futureInterface.future();
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
