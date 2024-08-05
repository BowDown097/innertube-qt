#include "video.h"
#include <QJsonArray>
#include <QLocale>

namespace InnertubeObjects
{
    Video::Video(const QJsonValue& videoRenderer)
        : descriptionSnippet(videoRenderer["descriptionSnippet"]),
          inlinePlaybackEndpoint(videoRenderer["inlinePlaybackEndpoint"]),
          longBylineText(videoRenderer["longBylineText"]),
          menu(videoRenderer["menu"]["menuRenderer"]),
          navigationEndpoint(videoRenderer["navigationEndpoint"]),
          searchVideoResultEntityKey(videoRenderer["searchVideoResultEntityKey"].toString()),
          shortBylineText(videoRenderer["shortBylineText"]),
          shortViewCountText(videoRenderer["shortViewCountText"]),
          showActionMenu(videoRenderer["showActionMenu"].toBool()),
          thumbnail(videoRenderer["thumbnail"]),
          title(videoRenderer["title"]),
          videoId(videoRenderer["videoId"].toString()),
          viewCountText(videoRenderer["viewCountText"])
    {
        const QJsonArray badgesArr = videoRenderer["badges"].toArray();
        for (const QJsonValue& badge : badgesArr)
            badges.append(MetadataBadge(badge["metadataBadgeRenderer"]));

        if (!isLive()) // lengthText and publishedTimeText do not exist for live videos
        {
            if (videoRenderer["lengthText"].isObject())
            {
                lengthText = InnertubeString(videoRenderer["lengthText"]);
            }
            else
            {
                const QJsonArray thumbnailOverlays = videoRenderer["thumbnailOverlays"].toArray();
                auto timeOverlay = std::ranges::find_if(thumbnailOverlays, [](const QJsonValue& v) {
                    return v["thumbnailOverlayTimeStatusRenderer"].isObject();
                });
                if (timeOverlay != thumbnailOverlays.end())
                {
                    const QJsonValue& timeOverlayVal = *timeOverlay;
                    lengthText = InnertubeString(timeOverlayVal["thumbnailOverlayTimeStatusRenderer"]["text"]);
                }
            }

            if (videoRenderer["upcomingEventData"].isObject())
            {
                QJsonValue upcomingEventData = videoRenderer["upcomingEventData"];
                InnertubeString upcomingEventText = InnertubeString(upcomingEventData["upcomingEventText"]);
                long startTime = upcomingEventData["startTime"].toString().toLong();
                QString fmt = QStringLiteral("%1, %2").arg(QLocale::system().dateFormat(QLocale::ShortFormat),
                                                           QLocale::system().timeFormat(QLocale::ShortFormat));

                upcomingEventText.text = upcomingEventText.text.replace("DATE_PLACEHOLDER", QDateTime::fromSecsSinceEpoch(startTime).toString(fmt));
                publishedTimeText = upcomingEventText;
            }
            else
            {
                publishedTimeText = InnertubeString(videoRenderer["publishedTimeText"]);
            }
        }

        owner = VideoOwner(
            videoRenderer["ownerText"].isObject() ? videoRenderer["ownerText"] : videoRenderer["shortBylineText"],
            videoRenderer["channelThumbnail"].isObject() ? videoRenderer["channelThumbnail"] : videoRenderer["channelThumbnailSupportedRenderers"],
            videoRenderer["ownerBadges"].toArray()
        );
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
        QTime out = QTime::fromString(lengthText.text, "h:mm:ss");
        if (!out.isValid())
            out = QTime::fromString(lengthText.text, "m:ss");
        return out;
    }
}
