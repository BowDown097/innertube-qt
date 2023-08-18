#include "video.h"
#include <QJsonArray>
#include <QLocale>

namespace InnertubeObjects
{
    Video::Video(const QJsonValue& videoRenderer, bool isGridVideo, const InnertubeString& shelf)
        : descriptionSnippet(videoRenderer["descriptionSnippet"]),
          longBylineText(videoRenderer["longBylineText"]),
          navigationEndpoint(videoRenderer["navigationEndpoint"]),
          shelf(shelf),
          shortBylineText(videoRenderer["shortBylineText"]),
          shortViewCountText(videoRenderer["shortViewCountText"]),
          showActionMenu(videoRenderer["showActionMenu"].toBool()),
          thumbnail(videoRenderer["videoId"].toString()),
          title(videoRenderer["title"]),
          videoId(videoRenderer["videoId"].toString()),
          viewCountText(videoRenderer["viewCountText"])
    {
        isLive = videoRenderer["badges"][0]["metadataBadgeRenderer"]["style"].toString() == "BADGE_STYLE_TYPE_LIVE_NOW";
        if (!isLive) // lengthText and publishedTimeText do not exist for live videos
        {
            if (isGridVideo)
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
            else
            {
                lengthText = InnertubeString(videoRenderer["lengthText"]);
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

        owner = isGridVideo
                ? VideoOwner(videoRenderer["shortBylineText"], videoRenderer["channelThumbnail"], videoRenderer["ownerBadges"], true)
                : VideoOwner(videoRenderer["ownerText"], videoRenderer["channelThumbnailSupportedRenderers"], videoRenderer["ownerBadges"], false);
    }

    QTime Video::length() const
    {
        QTime out = QTime::fromString(lengthText.text, "h:mm:ss");
        if (!out.isValid())
            out = QTime::fromString(lengthText.text, "m:ss");
        return out;
    }
}
