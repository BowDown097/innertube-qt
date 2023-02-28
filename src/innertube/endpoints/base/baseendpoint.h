#ifndef BASEENDPOINT_H
#define BASEENDPOINT_H
#include "innertube/itc-objects/innertubeauthstore.h"
#include "httplib.h"

class InnerTube;
namespace InnertubeEndpoints
{
    class BaseEndpoint
    {
    protected:
        QByteArray get(const QString& endpoint, InnertubeContext* context, InnertubeAuthStore* authStore, const QJsonObject& body);
    private:
        QByteArray getData(httplib::Client& client, const std::string& path, const QJsonObject& body);
        void setNeededHeaders(httplib::Client& client, InnertubeContext* context, InnertubeAuthStore* authStore);
    };
}

#endif // BASEENDPOINT_H
