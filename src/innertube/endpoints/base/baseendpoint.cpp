#include "baseendpoint.h"
#include "httprequest.h"
#include "innertube/itc-objects/innertubeauthstore.h"
#include <QJsonDocument>

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

            HttpReply* reply = HttpRequest()
                .withAttribute(QNetworkRequest::CookieSaveControlAttribute, QNetworkRequest::Manual)
                .withHeaders(getNeededHeaders(context, authStore))
                .post(path, QJsonDocument(body).toJson(QJsonDocument::Compact));

            QObject::connect(reply, &HttpReply::finished, reply, [futureInterface](const HttpReply& reply) mutable {
                futureInterface.reportResult(QJsonDocument::fromJson(reply.readAll()).object());
                futureInterface.reportFinished();
            });

            return futureInterface.future();
        }

        QList<std::pair<QByteArray, QByteArray>> getNeededHeaders(
            const InnertubeContext* context, const InnertubeAuthStore* authStore)
        {
            QList<std::pair<QByteArray, QByteArray>> headers;

            if (authStore->populated())
            {
                headers.emplaceBack("Authorization", authStore->generateSAPISIDHash().toUtf8());
                headers.emplaceBack("Cookie", authStore->toCookieString().toUtf8());
                headers.emplaceBack("X-Goog-AuthUser", "0");
            }

            headers.emplaceBack("Content-Type", "application/json");
            headers.emplaceBack("X-Goog-Visitor-Id", context->client.visitorData.toLatin1());
            headers.emplaceBack("X-YOUTUBE-CLIENT-NAME", QByteArray::number(static_cast<int>(context->client.clientType)));
            headers.emplaceBack("X-YOUTUBE-CLIENT-VERSION", context->client.clientVersion.toLatin1());
            headers.emplaceBack("X-ORIGIN", "https://www.youtube.com");

            return headers;
        }

        QFuture<void> getPlain(
            const QString& path, const QJsonObject& body,
            const InnertubeContext* context, const InnertubeAuthStore* authStore)
        {
            QFutureInterface<void> futureInterface;
            futureInterface.reportStarted();

            HttpReply* reply = HttpRequest()
                .withAttribute(QNetworkRequest::CookieSaveControlAttribute, QNetworkRequest::Manual)
                .withHeaders(getNeededHeaders(context, authStore))
                .post(path, QJsonDocument(body).toJson(QJsonDocument::Compact));

            QObject::connect(reply, &HttpReply::finished, reply, [futureInterface]() mutable {
                futureInterface.reportFinished();
            });

            return futureInterface.future();
        }
    }
}
