#include "navigationsubscribeendpoint.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    NavigationSubscribeEndpoint::NavigationSubscribeEndpoint(const QJsonValue& subscribeEndpoint)
        : params(subscribeEndpoint["params"].toString())
    {
        const QJsonArray channelIdsJson = subscribeEndpoint["channelIds"].toArray();
        for (const QJsonValue& v : channelIdsJson)
            channelIds.append(v.toString());
    }
}
