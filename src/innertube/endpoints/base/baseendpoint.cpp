#include "baseendpoint.h"
#include "innertube/itc-objects/innertubeauthstore.h"
#include "sslhttprequest.h"
#include <QEventLoop>
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    namespace EndpointMethods
    {
        QJsonValue getData(const QString& path, const QVariantMap& headers, const QJsonObject& body)
        {
            QScopedPointer<SslHttpRequest> req(new SslHttpRequest(path, SslHttpRequest::RequestMethod::Post));
            req->setBody(body);
            req->setHeaders(headers);
            req->send();

            QEventLoop loop;
            QObject::connect(req.data(), &SslHttpRequest::finished, &loop, &QEventLoop::quit);
            loop.exec();

            return QJsonDocument::fromJson(req->payload()).object();
        }

        QVariantMap getNeededHeaders(const InnertubeContext* context, const InnertubeAuthStore* authStore)
        {
            QVariantMap headers;

            if (authStore->populated())
            {
                headers.insert({
                    { "Authorization", authStore->generateSAPISIDHash() },
                    { "Cookie", authStore->toCookieString() },
                    { "X-Goog-AuthUser", "0" }
                });
            }

            headers.insert({
                { "X-Goog-Visitor-Id", context->client.visitorData },
                { "X-YOUTUBE-CLIENT-NAME", static_cast<int>(context->client.clientType) },
                { "X-YOUTUBE-CLIENT-VERSION", context->client.clientVersion },
                { "X-ORIGIN", "https://www.youtube.com" }
            });

            return headers;
        }
    }
}
