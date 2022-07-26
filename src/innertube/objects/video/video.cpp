#include "video.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QLocale>

namespace InnertubeObjects
{
    Video::Video(const QJsonValue& videoRenderer, bool isGridVideo, const InnertubeString& shelf) : shelf(shelf)
    {
        const QJsonObject rendererObj = videoRenderer.toObject();
        isLive = rendererObj.contains("badges")
                ? videoRenderer["badges"].toArray()[0].toObject()["metadataBadgeRenderer"].toObject()["style"].toString() == "BADGE_STYLE_TYPE_LIVE_NOW"
                : false;

        if (!isLive) // lengthText and publishedTimeText do not exist for live videos
        {
            if (isGridVideo)
            {
                const QJsonArray thumbnailOverlays = videoRenderer["thumbnailOverlays"].toArray();
                for (const QJsonValue& v : thumbnailOverlays)
                {
                    const QJsonObject timeStatus = v["thumbnailOverlayTimeStatusRenderer"].toObject();
                    if (timeStatus.isEmpty()) continue;
                    lengthText = InnertubeString(timeStatus["text"]);
                }
            }
            else
            {
                lengthText = InnertubeString(videoRenderer["lengthText"]);
            }

            if (rendererObj.contains("upcomingEventData"))
            {
                QJsonValue upcomingEventData = videoRenderer["upcomingEventData"];
                InnertubeString upcomingEventText = InnertubeString(upcomingEventData["upcomingEventText"]);
                long startTime = upcomingEventData["startTime"].toString().toLong();
                QString fmt = QStringLiteral("%1, %2").arg(QLocale::system().dateFormat(QLocale::ShortFormat), QLocale::system().timeFormat(QLocale::ShortFormat));

                upcomingEventText.text = upcomingEventText.text.replace("DATE_PLACEHOLDER", QDateTime::fromSecsSinceEpoch(startTime).toString(fmt));
                publishedTimeText = upcomingEventText;
            }
            else
            {
                publishedTimeText = InnertubeString(videoRenderer["publishedTimeText"]);
            }
        }

        videoId = videoRenderer["videoId"].toString();
        owner = isGridVideo
                ? VideoOwner(videoRenderer["shortBylineText"], videoRenderer["channelThumbnail"], true)
                : VideoOwner(videoRenderer["ownerText"], videoRenderer["channelThumbnailSupportedRenderers"], false);
        shortViewCountText = InnertubeString(videoRenderer["shortViewCountText"]);
        title = InnertubeString(videoRenderer["title"]);
        viewCountText = InnertubeString(videoRenderer["viewCountText"]);
        thumbnail = VideoThumbnail(videoId);
        startTimeSeconds = videoRenderer["navigationEndpoint"]["watchEndpoint"]["startTimeSeconds"].toInt();
    }
}
