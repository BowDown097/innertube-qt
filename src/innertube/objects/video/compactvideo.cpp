#include "compactvideo.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    CompactVideo::CompactVideo(const QJsonValue& compactVideoRenderer)
        : BaseVideo(compactVideoRenderer),
          accessibilityLabel(compactVideoRenderer["accessibility"]["accessibilityData"]["label"].toString()),
          channelThumbnail(compactVideoRenderer["channelThumbnail"]["thumbnails"]),
          publishedTimeText(compactVideoRenderer["publishedTimeText"]),
          richThumbnail(compactVideoRenderer["richThumbnail"]["movingThumbnailRenderer"]),
          shortViewCountText(compactVideoRenderer["shortViewCountText"]),
          viewCountText(compactVideoRenderer["viewCountText"])
    {
        const QJsonArray badgesJson = compactVideoRenderer["badges"].toArray();
        for (const QJsonValue& badge : badgesJson)
            badges.append(MetadataBadge(badge["metadataBadgeRenderer"]));

        const QJsonArray ownerBadgesJson = compactVideoRenderer["ownerBadges"].toArray();
        for (const QJsonValue& ownerBadge : ownerBadgesJson)
            ownerBadges.append(MetadataBadge(ownerBadge["metadataBadgeRenderer"]));
    }

    bool CompactVideo::isLive() const
    {
        return std::ranges::find(badges, "BADGE_STYLE_TYPE_LIVE_NOW", &MetadataBadge::style) != badges.end();
    }

    BasicChannel CompactVideo::owner() const
    {
        return BasicChannel {
            .icon = channelThumbnail,
            .id = shortBylineText.runs[0].navigationEndpoint["browseEndpoint"]["browseId"].toString(),
            .name = shortBylineText.text
        };
    }
}
