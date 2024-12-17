#pragma once
#include "innertube/objects/lottiedata.h"
#include "innertube/objects/images/responsiveimage.h"

namespace InnertubeObjects
{
    struct ThumbnailBadgeViewModel
    {
        QString animatedText;
        QString animationActivationEntityKey;
        QString animationActivationEntitySelectorType;
        QString animationActivationTargetId;
        QString badgeStyle;
        ResponsiveImage icon;
        LottieData lottieData;
        QString position;
        QString text;

        ThumbnailBadgeViewModel() = default;
        explicit ThumbnailBadgeViewModel(const QJsonValue& thumbnailBadgeViewModel)
            : animatedText(thumbnailBadgeViewModel["animatedText"].toString()),
              animationActivationEntityKey(thumbnailBadgeViewModel["animationActivationEntityKey"].toString()),
              animationActivationEntitySelectorType(thumbnailBadgeViewModel["animationActivationEntitySelectorType"].toString()),
              animationActivationTargetId(thumbnailBadgeViewModel["animationActivationTargetId"].toString()),
              badgeStyle(thumbnailBadgeViewModel["badgeStyle"].toString()),
              icon(thumbnailBadgeViewModel["icon"]["sources"]),
              lottieData(thumbnailBadgeViewModel["lottieData"]),
              position(thumbnailBadgeViewModel["position"].toString()),
              text(thumbnailBadgeViewModel["text"].toString()) {}
    };
}
