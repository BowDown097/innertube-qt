#pragma once
#include "responsiveimage.h"

namespace InnertubeObjects
{
    struct ImageWithAccessibility : ResponsiveImage
    {
        QString accessibilityLabel;

        ImageWithAccessibility() = default;
        explicit ImageWithAccessibility(const QJsonValue& data)
            : ResponsiveImage(data["thumbnails"]),
              accessibilityLabel(data["accessibility"]["accessibilityData"]["label"].toString()) {}
    };
}
