#ifndef BASEENDPOINT_H
#define BASEENDPOINT_H
#include "innertube/itc-objects/innertubeauthstore.h"
#include "qthttplib.h"

class InnerTube;
namespace InnertubeEndpoints
{
    class BaseEndpoint
    {
    protected:
        QByteArray get(const QString& endpoint, InnertubeContext* context, InnertubeAuthStore* authStore, const QJsonObject& body);
    private:
        QByteArray getData(qthttplib::Client* client, const QString& path, const QJsonObject& body);
        void setNeededHeaders(qthttplib::Client* client, InnertubeContext* context, InnertubeAuthStore* authStore);
    };
}

#endif // BASEENDPOINT_H
