#ifndef SUBSCRIBEBUTTON_H
#define SUBSCRIBEBUTTON_H
#include "innertube/objects/innertubestring.h"
#include "innertube/objects/navigation/navigationsubscribeendpoint.h"

namespace InnertubeObjects
{
    class SubscribeButton
    {
    public:
        InnertubeString buttonText;
        QString channelId;
        bool enabled;
        QList<NavigationSubscribeEndpoint> onSubscribeEndpoints;
        QList<NavigationSubscribeEndpoint> onUnsubscribeEndpoints;
        // TODO: notificationPreferenceButton
        bool showPreferences;
        QString subscribeAccessibility;
        bool subscribed;
        InnertubeString subscribedButtonText;
        QString subscribedEntityKey;
        QString targetId;
        QString trackingParams;
        QString type;
        QString unsubscribeAccessibility;
        InnertubeString unsubscribeButtonText;
        InnertubeString unsubscribedButtonText;

        SubscribeButton() {}
        explicit SubscribeButton(const QJsonValue& subscribeButtonRenderer);
    };
}

#endif // SUBSCRIBEBUTTON_H
