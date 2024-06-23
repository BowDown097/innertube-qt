#pragma once
#include "innertube/objects/entitymutation.h"
#include "subscribebuttoncontent.h"

namespace InnertubeObjects
{
    struct SubscribeButtonViewModel
    {
        QString backgroundStyle;
        QString bellAllAccessibility;
        QString bellDisabledAccessibility;
        QString bellOccasionalAccessibility;
        QString bellOffAccessibility;
        QString buttonSize;
        QString channelId;
        bool disableNotificationBell{};
        bool disableSubscribeButton{};
        QJsonValue onShowSubscriptionOptions;
        QString stateEntityStoreKey;
        QString subsNotificationStateKey;
        SubscribeButtonContent subscribeButtonContent;
        QString subscribedStateStyle;
        SubscribeButtonContent unsubscribeButtonContent;
        QString unsubscribedStateStyle;

        SubscribeButtonViewModel() = default;
        explicit SubscribeButtonViewModel(const QJsonValue& subscribeButtonViewModel)
            : backgroundStyle(subscribeButtonViewModel["backgroundStyle"].toString()),
              bellAllAccessibility(subscribeButtonViewModel["bellAccessibilityData"]["allLabel"].toString()),
              bellDisabledAccessibility(subscribeButtonViewModel["bellAccessibilityData"]["disabledLabel"].toString()),
              bellOccasionalAccessibility(subscribeButtonViewModel["bellAccessibilityData"]["occasionalLabel"].toString()),
              bellOffAccessibility(subscribeButtonViewModel["bellAccessibilityData"]["offLabel"].toString()),
              buttonSize(subscribeButtonViewModel["buttonStyle"]["buttonSize"].toString()),
              channelId(subscribeButtonViewModel["channelId"].toString()),
              disableNotificationBell(subscribeButtonViewModel["disableNotificationBell"].toBool()),
              disableSubscribeButton(subscribeButtonViewModel["disableSubscribeButton"].toBool()),
              onShowSubscriptionOptions(subscribeButtonViewModel["onShowSubscriptionOptions"]),
              stateEntityStoreKey(subscribeButtonViewModel["stateEntityStoreKey"].toString()),
              subsNotificationStateKey(subscribeButtonViewModel["notificationStateEntityStoreKeys"]
                                                               ["subsNotificationStateKey"].toString()),
              subscribeButtonContent(subscribeButtonViewModel["subscribeButtonContent"]),
              subscribedStateStyle(subscribeButtonViewModel["buttonStyle"]["subscribedStateStyle"].toString()),
              unsubscribeButtonContent(subscribeButtonViewModel["unsubscribeButtonContent"]),
              unsubscribedStateStyle(subscribeButtonViewModel["buttonStyle"]["unsubscribedStateStyle"].toString()) {}

        bool isSubscribed(const QList<InnertubeObjects::EntityMutation>& mutations) const;
    };
}
