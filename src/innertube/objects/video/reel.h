#pragma once
#include "innertube/objects/images/responsiveimage.h"
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    struct Reel
    {
        QString accessibilityLabel;
        QString headline;
        QString style;
        ResponsiveImage thumbnail;
        QString videoId;
        QString videoType;
        InnertubeString viewCountText;

        explicit Reel(const QJsonValue& reelItemRenderer)
            : accessibilityLabel(reelItemRenderer["accessibility"]["accessibilityData"]["label"].toString()),
              headline(reelItemRenderer["headline"]["simpleText"].toString()),
              style(reelItemRenderer["style"].toString()),
              thumbnail(reelItemRenderer["thumbnail"]["thumbnails"]),
              videoId(reelItemRenderer["videoId"].toString()),
              videoType(reelItemRenderer["videoType"].toString()),
              viewCountText(reelItemRenderer["viewCountText"]) {}
    };
}
