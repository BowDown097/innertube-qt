#pragma once
#include <QJsonObject>
#include <QVariantMap>

class InnerTube;
class InnertubeAuthStore;
class InnertubeContext;

// the key thankfully works on any client, though in theory it shouldn't - hopefully this never changes
#define YTI_REQUEST_TEMPLATE \
QStringLiteral("https://www.youtube.com/youtubei/v1/%1?key=AIzaSyAO_FJ2SlqU8Q4STEHLGCilw_Y9_11qcW8&prettyPrint=false")

namespace InnertubeEndpoints
{
    namespace EndpointMethods
    {
        QPair<QString, QJsonValue> contextPair(InnertubeContext* context);
        QJsonValue getData(const QString& path, const QVariantMap& headers, const QJsonObject& body);
        QVariantMap getNeededHeaders(InnertubeContext* context, InnertubeAuthStore* authStore);
    }

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
    struct BaseEndpoint
    {
        /**
         * @brief Gets the raw response of an Innertube request.
         * @details Unless if you absolutely know what you're doing or are not using the WEB client, you likely want to use @ref InnerTube::get.
         * @param endpoint  The raw endpoint name.
         * @param body  The JSON body of the request.
         * @return The request's response body.
         */
        static QJsonValue get(InnertubeContext* context, InnertubeAuthStore* authStore, const QJsonObject& body)
        {
            return EndpointMethods::getData(
                YTI_REQUEST_TEMPLATE.arg(endpoint.data),
                EndpointMethods::getNeededHeaders(context, authStore), body
            );
        }
    };
}
