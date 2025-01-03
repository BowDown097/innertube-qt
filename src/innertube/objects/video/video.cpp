#include "video.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    Video::Video(const QJsonValue& videoRenderer)
        : BaseVideo(videoRenderer),
          avatar(videoRenderer["avatar"]["decoratedAvatarViewModel"]),
          channelThumbnailSupportedRenderers(videoRenderer
              ["channelThumbnailSupportedRenderers"]["channelThumbnailWithLinkRenderer"]),
          descriptionSnippet(videoRenderer["descriptionSnippet"]),
          inlinePlaybackEndpoint(videoRenderer["inlinePlaybackEndpoint"]),
          isWatched(videoRenderer["isWatched"].toBool()),
          ownerText(videoRenderer["ownerText"]),
          publishedTimeText(videoRenderer["publishedTimeText"]),
          richThumbnail(videoRenderer["richThumbnail"]["movingThumbnailRenderer"]),
          searchVideoResultEntityKey(videoRenderer["searchVideoResultEntityKey"].toString()),
          shortViewCountText(videoRenderer["shortViewCountText"]),
          showActionMenu(videoRenderer["showActionMenu"].toBool()),
          viewCountText(videoRenderer["viewCountText"])
    {
        const QJsonArray badgesJson = videoRenderer["badges"].toArray();
        for (const QJsonValue& badge : badgesJson)
            badges.append(MetadataBadge(badge["metadataBadgeRenderer"]));

        const QJsonArray buttonsJson = videoRenderer["buttons"].toArray();
        for (const QJsonValue& button : buttonsJson)
            buttons.append(ToggleButton(button["toggleButtonRenderer"]));

        const QJsonArray detailedMetadataSnippetsJson = videoRenderer["detailedMetadataSnippets"].toArray();
        for (const QJsonValue& snippet : detailedMetadataSnippetsJson)
            detailedMetadataSnippets.append(MetadataSnippet(snippet));

        const QJsonArray ownerBadgesJson = videoRenderer["ownerBadges"].toArray();
        for (const QJsonValue& ownerBadge : ownerBadgesJson)
            ownerBadges.append(MetadataBadge(ownerBadge["metadataBadgeRenderer"]));

        if (const QJsonValue upcomingEventDataJson = videoRenderer["upcomingEventData"]; upcomingEventDataJson.isObject())
            upcomingEventData = UpcomingEventData(upcomingEventDataJson);
    }

    bool Video::isLive() const
    {
        return std::ranges::any_of(badges, [](const MetadataBadge& b) { return b.style == "BADGE_STYLE_TYPE_LIVE_NOW"; });
    }

    bool Video::isReel() const
    {
        return navigationEndpoint["reelWatchEndpoint"].isObject();
    }

    QString Video::ownerId() const
    {
        if (ownerText.runs.isEmpty())
            return QString();
        return ownerText.runs[0].navigationEndpoint["browseEndpoint"]["browseId"].toString();
    }

    QString Video::publishedTimeDisplay() const
    {
        if (upcomingEventData.has_value())
            return upcomingEventData->formattedEventText();
        return publishedTimeText.text;
    }
}
