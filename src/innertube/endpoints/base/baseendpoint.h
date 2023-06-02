#ifndef BASEENDPOINT_H
#define BASEENDPOINT_H
#include "cpr/cpr.h"
#include "innertube/itc-objects/innertubeauthstore.h"

class InnerTube;
namespace InnertubeEndpoints
{
    class BaseEndpoint
    {
    protected:
        QByteArray get(const QString& endpoint, InnertubeContext* context, InnertubeAuthStore* authStore, const QJsonObject& body);
    private:
        QByteArray getData(const QString& path, const cpr::Header& headers, const QJsonObject& body);
        cpr::Header getNeededHeaders(InnertubeContext* context, InnertubeAuthStore* authStore);
    };
}

#endif // BASEENDPOINT_H
