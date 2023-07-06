#ifndef BASEENDPOINT_H
#define BASEENDPOINT_H
#include "innertube/itc-objects/innertubeauthstore.h"
#include "sslhttprequest.h"

class InnerTube;
namespace InnertubeEndpoints
{
    class BaseEndpoint
    {
    public:
        QByteArray get(const QString& endpoint, InnertubeContext* context, InnertubeAuthStore* authStore, const QJsonObject& body);
    private:
        QByteArray getData(const QString& path, const QMap<QString, QString>& headers, const QJsonObject& body);
        QMap<QString, QString> getNeededHeaders(InnertubeContext* context, InnertubeAuthStore* authStore);
    };
}

#endif // BASEENDPOINT_H
