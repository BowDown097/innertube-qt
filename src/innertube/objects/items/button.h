#pragma once
#include "innertube/objects/innertubestring.h"
#include <optional>

namespace InnertubeObjects
{
    struct Button
    {
        QString accessibilityLabel;
        std::optional<QJsonValue> command; // available if serviceEndpoint is not
        QString iconType;
        bool isDisabled{};
        std::optional<QJsonValue> serviceEndpoint; // available if command is not
        QString size;
        QString style;
        QString targetId;
        InnertubeString text;
        QString tooltip;

        Button() = default;
        explicit Button(const QJsonValue& buttonRenderer)
            : accessibilityLabel(buttonRenderer["accessibilityData"]["accessibilityData"]["label"].toString()),
              command(buttonRenderer["command"].isObject()
                  ? std::make_optional<QJsonValue>(buttonRenderer["command"]) : std::nullopt),
              iconType(buttonRenderer["icon"]["iconType"].toString()),
              isDisabled(buttonRenderer["isDisabled"].toBool()),
              serviceEndpoint(buttonRenderer["serviceEndpoint"].isObject()
                  ? std::make_optional<QJsonValue>(buttonRenderer["serviceEndpoint"]) : std::nullopt),
              size(buttonRenderer["size"].toString()),
              style(buttonRenderer["style"].toString()),
              targetId(buttonRenderer["targetId"].toString()),
              text(buttonRenderer["text"]),
              tooltip(buttonRenderer["tooltip"].toString()) {}
    };
}
