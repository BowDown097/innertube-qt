#pragma once
#include "notificationpreferencebutton.h"

namespace InnertubeObjects
{
    struct SubscribeButton
    {
        InnertubeString buttonText;
        QString channelId;
        bool enabled{};
        NotificationPreferenceButton notificationPreferenceButton;
        QJsonValue onSubscribeEndpoints;
        QJsonValue onUnsubscribeEndpoints;
        bool showPreferences{};
        QString subscribeAccessibility;
        bool subscribed{};
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
              onSubscribeEndpoints(subscribeButtonRenderer["onSubscribeEndpoints"]),
              onUnsubscribeEndpoints(subscribeButtonRenderer["onUnsubscribeEndpoints"]),
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
