#include "video.h"
#include <QJsonArray>
#include <QLocale>

namespace InnertubeObjects
{
    Video::Video(const QJsonValue& videoRenderer)
        : avatar(videoRenderer["avatar"]["decoratedAvatarViewModel"]),
          channelThumbnailSupportedRenderers(videoRenderer
              ["channelThumbnailSupportedRenderers"]["channelThumbnailWithLinkRenderer"]),
          descriptionSnippet(videoRenderer["descriptionSnippet"]),
          inlinePlaybackEndpoint(videoRenderer["inlinePlaybackEndpoint"]),
          isWatched(videoRenderer["isWatched"].toBool()),
          lengthText(videoRenderer["lengthText"]),
          longBylineText(videoRenderer["longBylineText"]),
          menu(videoRenderer["menu"]["menuRenderer"]),
          navigationEndpoint(videoRenderer["navigationEndpoint"]),
          ownerText(videoRenderer["ownerText"]),
          publishedTimeText(videoRenderer["publishedTimeText"]),
          richThumbnail(videoRenderer["richThumbnail"]["movingThumbnailRenderer"]),
          searchVideoResultEntityKey(videoRenderer["searchVideoResultEntityKey"].toString()),
          shortBylineText(videoRenderer["shortBylineText"]),
          shortViewCountText(videoRenderer["shortViewCountText"]),
          showActionMenu(videoRenderer["showActionMenu"].toBool()),
          thumbnail(videoRenderer["thumbnail"]),
          title(videoRenderer["title"]),
          videoId(videoRenderer["videoId"].toString()),
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

        const QJsonArray thumbnailOverlaysJson = videoRenderer["thumbnailOverlays"].toArray();
        for (const QJsonValue& overlay : thumbnailOverlaysJson)
        {
            if (const QJsonValue endorsement = overlay["thumbnailOverlayEndorsementRenderer"]; endorsement.isObject())
                thumbnailOverlays.append(ThumbnailOverlayEndorsement(endorsement));
            else if (const QJsonValue inlineUnplayable = overlay["thumbnailOverlayInlineUnplayableRenderer"]; inlineUnplayable.isObject())
                thumbnailOverlays.append(ThumbnailOverlayInlineUnplayable(inlineUnplayable));
            else if (const QJsonValue loadingPreview = overlay["thumbnailOverlayLoadingPreviewRenderer"]; loadingPreview.isObject())
                thumbnailOverlays.append(ThumbnailOverlayLoadingPreview(loadingPreview));
            else if (const QJsonValue nowPlaying = overlay["thumbnailOverlayNowPlayingRenderer"]; nowPlaying.isObject())
                thumbnailOverlays.append(ThumbnailOverlayNowPlaying(nowPlaying));
            else if (const QJsonValue resumePlayback = overlay["thumbnailOverlayResumePlaybackRenderer"]; resumePlayback.isObject())
                thumbnailOverlays.append(ThumbnailOverlayResumePlayback(resumePlayback));
            else if (const QJsonValue timeStatus = overlay["thumbnailOverlayTimeStatusRenderer"]; timeStatus.isObject())
                thumbnailOverlays.append(ThumbnailOverlayTimeStatus(timeStatus));
            else if (const QJsonValue toggleButton = overlay["thumbnailOverlayToggleButtonRenderer"]; toggleButton.isObject())
                thumbnailOverlays.append(ThumbnailOverlayToggleButton(toggleButton));
        }

        if (const QJsonValue upcomingEventDataJson = videoRenderer["upcomingEventData"]; upcomingEventDataJson.isObject())
            upcomingEventData = UpcomingEventData(upcomingEventDataJson);
    }

    bool Video::isLive() const
    {
        return std::ranges::any_of(badges, [](const MetadataBadge& b) { return b.style == "BADGE_STYLE_TYPE_LIVE_NOW"; });
    }

    // reels can still be of this type and not of the Reel type. blame innertube
    bool Video::isReel() const
    {
        return navigationEndpoint["reelWatchEndpoint"].isObject();
    }

    QTime Video::length() const
    {
        const InnertubeString& lengthDisplayText = lengthDisplay();

        QTime out = QTime::fromString(lengthDisplayText.text, "h:mm:ss");
        if (!out.isValid())
            out = QTime::fromString(lengthDisplayText.text, "m:ss");

        return out;
    }

    const InnertubeString& Video::lengthDisplay() const
    {
        for (const ThumbnailOverlay& overlay : thumbnailOverlays)
            if (const ThumbnailOverlayTimeStatus* timeStatus = std::get_if<ThumbnailOverlayTimeStatus>(&overlay))
                return timeStatus->text;

        return lengthText;
    }

    QString Video::ownerId() const
    {
        return ownerText.runs[0].navigationEndpoint["browseEndpoint"]["browseId"].toString();
    }

    QString Video::publishedTimeDisplay() const
    {
        if (upcomingEventData.has_value())
            return upcomingEventData->formattedEventText();
        return publishedTimeText.text;
    }
}
