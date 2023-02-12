#include "reel.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    Reel::Reel(const QJsonValue& reelItemRenderer)
        : accessibilityLabel(reelItemRenderer["accessibility"]["accessibilityData"]["label"].toString()),
          headline(reelItemRenderer["headline"]["simpleText"].toString()),
          style(reelItemRenderer["style"].toString()),
          videoId(reelItemRenderer["videoId"].toString()),
          videoType(reelItemRenderer["videoType"].toString()),
          viewCountText(reelItemRenderer["viewCountText"])
    {
        const QJsonArray thumbnailsJson = reelItemRenderer["thumbnail"]["thumbnails"].toArray();
        for (const QJsonValue& v : thumbnailsJson)
            thumbnails.append(GenericThumbnail(v));
    }
}
