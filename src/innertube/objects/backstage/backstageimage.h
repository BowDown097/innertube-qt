#pragma once
#include "innertube/objects/images/responsiveimage.h"

namespace InnertubeObjects
{
    struct BackstageImage
    {
        QString accessibilityLabel;
        QJsonValue command;
        ResponsiveImage image;

        explicit BackstageImage(const QJsonValue& backstageImageRenderer)
            : accessibilityLabel(backstageImageRenderer["accessibility"]["accessibilityData"]["label"].toString()),
              command(backstageImageRenderer["command"]),
              image(backstageImageRenderer["image"]["thumbnails"]) {}
    };
}
