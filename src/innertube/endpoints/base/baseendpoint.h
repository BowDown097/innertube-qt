#pragma once
#include "innertube/innertubeexception.h"
#include "innertube/itc-objects/innertubecontext.h"
#include <QFuture>
#include <QJsonObject>

class InnertubeAuthStore;
class QNetworkRequest;

// the key thankfully works on any client, though in theory it shouldn't - hopefully this never changes
constexpr QLatin1String RequestTemplate(
    "https://www.youtube.com/youtubei/v1/%1?key=AIzaSyAO_FJ2SlqU8Q4STEHLGCilw_Y9_11qcW8&prettyPrint=false");

namespace InnertubeEndpoints
{
    namespace EndpointMethods
    {
        QFuture<QJsonValue> getData(
            const QString& path, const QJsonObject& body,
            const InnertubeContext* context, const InnertubeAuthStore* authStore);
        QFuture<void> getPlain(
            const QString& path, const QJsonObject& body,
            const InnertubeContext* context, const InnertubeAuthStore* authStore);
        void setNeededHeaders(
            QNetworkRequest& req, const InnertubeContext* context,
            const InnertubeAuthStore* authStore);
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
        static QFuture<QJsonValue> get(
            const InnertubeContext* context, const InnertubeAuthStore* authStore, const QJsonObject& body)
        {
            return EndpointMethods::getData(RequestTemplate.arg(endpoint.data), body, context, authStore);
        }

        static QFuture<void> getPlain(
            const InnertubeContext* context, const InnertubeAuthStore* authStore, const QJsonObject& body)
        {
            return EndpointMethods::getPlain(RequestTemplate.arg(endpoint.data), body, context, authStore);
        }
    };

    template<typename EndpointType>
    static QFuture<EndpointType> prepare(
        const InnertubeContext* context, const InnertubeAuthStore* authStore, const QJsonObject& body)
    {
        QFutureInterface<EndpointType> futureInterface;
        futureInterface.reportStarted();

        EndpointType::get(context, authStore, body).then([futureInterface](QFuture<QJsonValue> f) mutable {
            try
            {
            #if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
                futureInterface.reportAndEmplaceResult(-1, f.result());
            #else
                futureInterface.reportResult(EndpointType(f.result()));
            #endif
                futureInterface.reportFinished();
            }
            catch (const InnertubeException& ie)
            {
                futureInterface.reportException(ie);
            }
        });

        return futureInterface.future();
    }
}
