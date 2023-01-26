#ifndef BASEENDPOINT_H
#define BASEENDPOINT_H
#include "CurlEasy.h"
#include "innertube/itc-objects/innertubeauthstore.h"

class InnerTube;
namespace InnertubeEndpoints
{
    class BaseEndpoint
    {
    protected:
        QByteArray get(const QString& endpoint, InnertubeContext* context, InnertubeAuthStore* authStore, CurlEasy* easy,
                       const QJsonObject& body);
    private:
        QByteArray getData(CurlEasy* easy, const QJsonObject& body);
        void setNeededHeaders(CurlEasy* easy, InnertubeContext* context, InnertubeAuthStore* authStore);
    };
}

#endif // BASEENDPOINT_H
