#ifndef BACKSTAGEIMAGE_H
#define BACKSTAGEIMAGE_H
#include "innertube/objects/responsiveimage.h"

namespace InnertubeObjects
{
    struct BackstageImage
    {
    public:
        QString accessibilityLabel;
        QJsonValue command;
        ResponsiveImage image;

        explicit BackstageImage(const QJsonValue& backstageImageRenderer)
            : accessibilityLabel(backstageImageRenderer["accessibility"]["accessibilityData"]["label"].toString()),
              command(backstageImageRenderer["command"]),
              image(backstageImageRenderer["image"]["thumbnails"]) {}
    };
}

#endif // BACKSTAGEIMAGE_H
