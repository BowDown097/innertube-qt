#pragma once
#include <QJsonValue>

namespace InnertubeObjects
{
    struct ThumbnailOverlayToggleButton
    {
        bool isToggled{};
        QString toggledAccessibilityLabel;
        QString toggledIconType;
        QJsonValue toggledServiceEndpoint;
        QString toggledTooltip;
        QString untoggledAccessibilityLabel;
        QString untoggledIconType;
        QJsonValue untoggledServiceEndpoint;
        QString untoggledTooltip;

        ThumbnailOverlayToggleButton() = default;
        explicit ThumbnailOverlayToggleButton(const QJsonValue& thumbnailOverlayToggleButtonRenderer)
            : isToggled(thumbnailOverlayToggleButtonRenderer["isToggled"].toBool()),
              toggledAccessibilityLabel(thumbnailOverlayToggleButtonRenderer
                  ["toggledAccessibility"]["accessibilityData"]["label"].toString()),
              toggledIconType(thumbnailOverlayToggleButtonRenderer["toggledIcon"]["iconType"].toString()),
              toggledServiceEndpoint(thumbnailOverlayToggleButtonRenderer["toggledServiceEndpoint"]),
              toggledTooltip(thumbnailOverlayToggleButtonRenderer["toggledTooltip"].toString()),
              untoggledAccessibilityLabel(thumbnailOverlayToggleButtonRenderer
                  ["untoggledAccessibility"]["accessibilityData"]["label"].toString()),
              untoggledIconType(thumbnailOverlayToggleButtonRenderer["untoggledIcon"]["iconType"].toString()),
              untoggledServiceEndpoint(thumbnailOverlayToggleButtonRenderer["untoggledServiceEndpoint"]),
              untoggledTooltip(thumbnailOverlayToggleButtonRenderer["untoggledTooltip"].toString()) {}
    };
}
