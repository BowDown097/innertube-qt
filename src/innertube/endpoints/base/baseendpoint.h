#ifndef BASEENDPOINT_H
#define BASEENDPOINT_H
#include "innertube/itc-objects/innertubeauthstore.h"
#include "sslhttprequest.h"

class InnerTube;
namespace InnertubeEndpoints
{
    /**
     * @brief The parent of all endpoint objects.
     */
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
        QByteArray get(const QString& endpoint, InnertubeContext* context, InnertubeAuthStore* authStore, const QJsonObject& body);
    private:
        QByteArray getData(const QString& path, const QMap<QString, QString>& headers, const QJsonObject& body);
        QMap<QString, QString> getNeededHeaders(InnertubeContext* context, InnertubeAuthStore* authStore);
    };
}

#endif // BASEENDPOINT_H
