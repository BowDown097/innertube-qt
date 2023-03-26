#ifndef SUBSCRIBEBUTTON_H
#define SUBSCRIBEBUTTON_H
#include "innertube/objects/innertubestring.h"
#include "notificationpreferencebutton.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    class SubscribeButton
    {
    public:
        InnertubeString buttonText;
        QString channelId;
        bool enabled;
        NotificationPreferenceButton notificationPreferenceButton;
        QJsonArray onSubscribeEndpoints;
        QJsonArray onUnsubscribeEndpoints;
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

        SubscribeButton() = default;
        explicit SubscribeButton(const QJsonValue& subscribeButtonRenderer)
            : buttonText(subscribeButtonRenderer["buttonText"]),
              channelId(subscribeButtonRenderer["channelId"].toString()),
              enabled(subscribeButtonRenderer["enabled"].toBool()),
              notificationPreferenceButton(subscribeButtonRenderer["notificationPreferenceButton"]["subscriptionNotificationToggleButtonRenderer"]),
              onSubscribeEndpoints(subscribeButtonRenderer["onSubscribeEndpoints"].toArray()),
              onUnsubscribeEndpoints(subscribeButtonRenderer["onUnsubscribeEndpoints"].toArray()),
              showPreferences(subscribeButtonRenderer["showPreferences"].toBool()),
              subscribeAccessibility(subscribeButtonRenderer["subscribeAccessibility"]["accessibilityData"]["label"].toString()),
              subscribed(subscribeButtonRenderer["subscribed"].toBool()),
              subscribedButtonText(subscribeButtonRenderer["subscribedButtonText"]),
              subscribedEntityKey(subscribeButtonRenderer["subscribedEntityKey"].toString()),
              targetId(subscribeButtonRenderer["targetId"].toString()),
              trackingParams(subscribeButtonRenderer["trackingParams"].toString()),
              type(subscribeButtonRenderer["type"].toString()),
              unsubscribeAccessibility(subscribeButtonRenderer["unsubscribeAccessibility"]["accessibilityData"]["label"].toString()),
              unsubscribeButtonText(subscribeButtonRenderer["unsubscribeButtonText"]),
              unsubscribedButtonText(subscribeButtonRenderer["unsubscribedButtonText"]) {}
    };
}

#endif // SUBSCRIBEBUTTON_H
