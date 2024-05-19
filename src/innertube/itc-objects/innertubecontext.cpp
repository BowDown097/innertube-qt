#include "innertubecontext.h"
#include <QJsonObject>

QJsonValue InnertubeContext::toJson() const
{
    return QJsonObject {
        { "clickTracking", clickTracking.toJson() },
        { "client", client.toJson() },
        { "request", request.toJson() },
        { "user", user.toJson() }
    };
}
