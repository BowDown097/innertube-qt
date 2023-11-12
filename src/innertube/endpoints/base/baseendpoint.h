#ifndef BASEENDPOINT_H
#define BASEENDPOINT_H
#include "innertube/itc-objects/innertubeauthstore.h"
#include "sslhttprequest.h"
#include <QEventLoop>

class InnerTube;
namespace InnertubeEndpoints
{
    template<size_t N>
    struct CompTimeStr
    {
        char data[N] {};
        consteval CompTimeStr(const char (&str)[N]) { std::copy_n(str, N, data); }
    };

    /**
     * @brief The parent of all endpoint objects.
     */
    template<CompTimeStr endpoint>
    class BaseEndpoint
    {
    public:
        /**
         * @brief Gets the raw response of an Innertube request.
         * @details Unless if you absolutely know what you're doing or are not using the WEB client, you likely want to use @ref InnerTube::get.
         * @param endpoint  The raw endpoint name.
         * @param body  The JSON body of the request.
         * @return The request's response body.
         */
        static QByteArray get(InnertubeContext* context, InnertubeAuthStore* authStore, const QJsonObject& body)
        {
            return getData(QStringLiteral("https://www.youtube.com/youtubei/v1/%1?key=AIzaSyAO_FJ2SlqU8Q4STEHLGCilw_Y9_11qcW8&prettyPrint=false").arg(endpoint.data),
                           getNeededHeaders(context, authStore), body);
        }
    private:
        static QByteArray getData(const QString& path, const QVariantMap& headers, const QJsonObject& body)
        {
            QScopedPointer<SslHttpRequest, QScopedPointerDeleteLater> req(new SslHttpRequest(path, SslHttpRequest::RequestMethod::Post));
            req->setBody(body);
            req->setHeaders(headers);
            req->send();

            QEventLoop loop;
            QObject::connect(req.data(), &SslHttpRequest::finished, &loop, &QEventLoop::quit);
            loop.exec();

            return req->payload();
        }

        static QVariantMap getNeededHeaders(InnertubeContext* context, InnertubeAuthStore* authStore)
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
    };
}

#endif // BASEENDPOINT_H
