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
        void getData(CurlEasy* easy, const QJsonObject& body, QByteArray& data);
        void setNeededHeaders(CurlEasy* easy, InnertubeContext* context, InnertubeAuthStore* authStore);
    };
}

#endif // BASEENDPOINT_H
