#include "baseendpoint.h"
#include "innertube/itc-objects/innertubeauthstore.h"
#include <QJsonDocument>
#include <QNetworkReply>

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

            QNetworkAccessManager* nam = new QNetworkAccessManager;

            QNetworkRequest req(path);
            req.setAttribute(QNetworkRequest::CookieSaveControlAttribute, QNetworkRequest::Manual);
            setNeededHeaders(req, context, authStore);

            QNetworkReply* reply = nam->post(req, QJsonDocument(body).toJson(QJsonDocument::Compact));

            QObject::connect(reply, &QNetworkReply::finished, reply, [futureInterface, nam, reply]() mutable {
                nam->deleteLater();
                reply->deleteLater();

                futureInterface.reportResult(QJsonDocument::fromJson(reply->readAll()).object());
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

            QNetworkAccessManager* nam = new QNetworkAccessManager;

            QNetworkRequest req(path);
            req.setAttribute(QNetworkRequest::CookieSaveControlAttribute, QNetworkRequest::Manual);
            setNeededHeaders(req, context, authStore);

            QNetworkReply* reply = nam->post(req, QJsonDocument(body).toJson(QJsonDocument::Compact));

            QObject::connect(reply, &QNetworkReply::finished, reply, [futureInterface, nam, reply]() mutable {
                nam->deleteLater();
                reply->deleteLater();
                futureInterface.reportFinished();
            });

            return futureInterface.future();
        }

        void setNeededHeaders(
            QNetworkRequest& req, const InnertubeContext* context,
            const InnertubeAuthStore* authStore)
        {
            if (authStore->populated())
            {
                req.setRawHeader("Authorization", authStore->generateSAPISIDHash().toUtf8());
                req.setRawHeader("Cookie", authStore->toCookieString().toUtf8());
                req.setRawHeader("X-Goog-AuthUser", "0");
            }

            req.setRawHeader("Content-Type", "application/json");
            req.setRawHeader("X-Goog-Visitor-Id", context->client.visitorData.toLatin1());
            req.setRawHeader("X-Youtube-Client-Name", QByteArray::number(static_cast<int>(context->client.clientType)));
            req.setRawHeader("X-Youtube-Client-Version", context->client.clientVersion.toLatin1());
            req.setRawHeader("X-Origin", "https://www.youtube.com");
        }
    }
}
