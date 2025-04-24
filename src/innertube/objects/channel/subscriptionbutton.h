#pragma once
#include <QJsonValue>

namespace InnertubeObjects
{
    struct SubscriptionButton
    {
        bool subscribed{};
        QString type;

        SubscriptionButton() = default;
        explicit SubscriptionButton(const QJsonValue& subscriptionButton)
            : subscribed(subscriptionButton["subscribed"].toBool()),
              type(subscriptionButton["type"].toString()) {}
    };
}
