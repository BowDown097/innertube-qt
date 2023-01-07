#ifndef NAVIGATIONSUBSCRIBEENDPOINT_H
#define NAVIGATIONSUBSCRIBEENDPOINT_H
#include <QJsonValue>

namespace InnertubeObjects
{
    class NavigationSubscribeEndpoint
    {
    public:
        QList<QString> channelIds;
        QString params;
        explicit NavigationSubscribeEndpoint(const QJsonValue& subscribeEndpoint);
    };
}

#endif // NAVIGATIONSUBSCRIBEENDPOINT_H
