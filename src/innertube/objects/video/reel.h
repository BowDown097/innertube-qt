#ifndef REEL_H
#define REEL_H
#include "innertube/objects/innertubestring.h"
#include "innertube/objects/responsiveimage.h"
#include "videoowner.h"

namespace InnertubeObjects
{
    struct Reel
    {
        QString accessibilityLabel;
        QString headline;
        ResponsiveImage image;
        VideoOwner owner;
        QString style;
        QString videoId;
        QString videoType;
        InnertubeString viewCountText;

        explicit Reel(const QJsonValue& reelItemRenderer)
            : accessibilityLabel(reelItemRenderer["accessibility"]["accessibilityData"]["label"].toString()),
              headline(reelItemRenderer["headline"]["simpleText"].toString()),
              image(reelItemRenderer["image"]["thumbnails"]),
              style(reelItemRenderer["style"].toString()),
              videoId(reelItemRenderer["videoId"].toString()),
              videoType(reelItemRenderer["videoType"].toString()),
              viewCountText(reelItemRenderer["viewCountText"]) {}
    };
}

#endif // REEL_H
