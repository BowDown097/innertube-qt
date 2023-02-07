#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    class ToggleButton
    {
    public:
        QString accessibilityLabel;
        QString defaultIcon;
        QJsonValue defaultServiceEndpoint;
        QString defaultTooltip;
        InnertubeString defaultText;
        bool isDisabled;
        bool isToggled;
        QString style;
        QString targetId;
        QString toggleButtonId;
        QJsonValue toggledServiceEndpoint;
        QString toggledStyle;
        InnertubeString toggledText;
        QString toggledTooltip;

        ToggleButton() {}
        ToggleButton(const QJsonValue& toggleButtonRenderer)
            : accessibilityLabel(toggleButtonRenderer["accessibility"]["label"].toString()),
              defaultIcon(toggleButtonRenderer["defaultIcon"]["iconType"].toString()),
              defaultServiceEndpoint(toggleButtonRenderer["defaultServiceEndpoint"]),
              defaultTooltip(toggleButtonRenderer["defaultTooltip"].toString()),
              defaultText(toggleButtonRenderer["defaultText"]),
              isDisabled(toggleButtonRenderer["isDisabled"].toBool()),
              isToggled(toggleButtonRenderer["isToggled"].toBool()),
              style(toggleButtonRenderer["style"]["styleType"].toString()),
              targetId(toggleButtonRenderer["targetId"].toString()),
              toggleButtonId(toggleButtonRenderer["toggleButtonSupportedData"]["toggleButtonIdData"]["id"].toString()),
              toggledServiceEndpoint(toggleButtonRenderer["toggledServiceEndpoint"]),
              toggledStyle(toggleButtonRenderer["toggledStyle"]["styleType"].toString()),
              toggledText(toggleButtonRenderer["toggledText"]),
              toggledTooltip(toggleButtonRenderer["toggledTooltip"].toString()) {}
    };
}

#endif // TOGGLEBUTTON_H
