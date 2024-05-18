#pragma once
#include "responsiveimage.h"

namespace InnertubeObjects
{
    struct ImageWithAccessibility
    {
        QString accessibilityLabel;
        ResponsiveImage image;

        ImageWithAccessibility() = default;
        explicit ImageWithAccessibility(const QJsonValue& data)
            : accessibilityLabel(data["accessibility"]["accessibilityData"]["label"].toString()),
              image(data["thumbnails"]) {}
    };
}
