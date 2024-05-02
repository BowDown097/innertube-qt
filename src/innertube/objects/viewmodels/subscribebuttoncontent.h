#pragma once
#include <QJsonValue>

namespace InnertubeObjects
{
    struct SubscribeButtonContent
    {
        QString accessibilityText;
        QString buttonText;
        QString imageName;
        QJsonValue onTapCommand;
        bool subscribeState;
        QString subscribeStateKey;

        SubscribeButtonContent() = default;
        explicit SubscribeButtonContent(const QJsonValue& content)
            : accessibilityText(content["accessibilityText"].toString()),
              buttonText(content["buttonText"].toString()),
              imageName(content["imageName"].toString()),
              onTapCommand(content["onTapCommand"]),
              subscribeState(content["subscribeState"]["subscribed"].toBool()),
              subscribeStateKey(content["subscribeState"]["key"].toString()) {}
    };
}
