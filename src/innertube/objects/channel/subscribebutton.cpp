#include "subscribebutton.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    SubscribeButton::SubscribeButton(const QJsonValue& subscribeButtonRenderer)
        : buttonText(subscribeButtonRenderer["buttonText"]),
          channelId(subscribeButtonRenderer["channelId"].toString()),
          enabled(subscribeButtonRenderer["enabled"].toBool()),
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
          unsubscribedButtonText(subscribeButtonRenderer["unsubscribedButtonText"])
    {
        const QJsonArray subscribeEndpoints = subscribeButtonRenderer["onSubscribeEndpoints"].toArray();
        for (const QJsonValue& v : subscribeEndpoints)
            onSubscribeEndpoints.append(NavigationSubscribeEndpoint(v["subscribeEndpoint"]));

        const QJsonArray unsubscribeEndpoints = subscribeButtonRenderer["onUnsubscribeEndpoints"].toArray();
        for (const QJsonValue& v : unsubscribeEndpoints)
            onUnsubscribeEndpoints.append(NavigationSubscribeEndpoint(v["signalServiceEndpoint"]["actions"][0]["openPopupAction"]["popup"]["confirmDialogRenderer"]["confirmButton"]["buttonRenderer"]["serviceEndpoint"]["unsubscribeEndpoint"]));
    }
}
