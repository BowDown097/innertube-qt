#ifndef BUTTON_H
#define BUTTON_H
#include "innertube/objects/innertubestring.h"
#include <optional>

namespace InnertubeObjects
{
    class Button
    {
    public:
        QString accessibilityLabel;
        std::optional<QJsonValue> command; // available if serviceEndpoint is not
        QString iconType;
        bool isDisabled = false;
        std::optional<QJsonValue> serviceEndpoint; // available if command is not
        QString size;
        QString style;
        QString targetId;
        InnertubeString text;
        QString tooltip;

        Button() = default;
        explicit Button(const QJsonValue& buttonRenderer)
            : accessibilityLabel(buttonRenderer["accessibilityData"]["accessibilityData"]["label"].toString()),
              command(std::make_optional<QJsonValue>(buttonRenderer["command"])),
              iconType(buttonRenderer["icon"]["iconType"].toString()),
              isDisabled(buttonRenderer["isDisabled"].toBool()),
              serviceEndpoint(std::make_optional<QJsonValue>(buttonRenderer["serviceEndpoint"])),
              size(buttonRenderer["size"].toString()),
              style(buttonRenderer["style"].toString()),
              targetId(buttonRenderer["targetId"].toString()),
              text(buttonRenderer["text"]),
              tooltip(buttonRenderer["tooltip"].toString()) {}
    };
}

#endif // BUTTON_H
