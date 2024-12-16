#pragma once
#include "innertube/objects/images/responsiveimage.h"

namespace InnertubeObjects
{
    struct ImageBannerViewModel
    {
        ResponsiveImage image;
        QJsonValue rendererContext;
        QString style;

        ImageBannerViewModel() = default;
        explicit ImageBannerViewModel(const QJsonValue& imageBannerViewModel)
            : image(imageBannerViewModel["image"]["sources"]),
              rendererContext(imageBannerViewModel["rendererContext"]),
              style(imageBannerViewModel["style"].toString()) {}
    };
}
