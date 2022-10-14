#include "innertubecontext.h"

QJsonObject InnertubeContext::toJson() const
{
    return {
        { "clickTracking", clickTracking.toJson() },
        { "client", client.toJson() },
        { "request", request.toJson() },
        { "user", user.toJson() }
    };
}
