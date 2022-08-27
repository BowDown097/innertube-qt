#ifndef VIDEO_H
#define VIDEO_H
#include "../innertubestring.h"
#include "videoowner.h"
#include "videothumbnail.h"

namespace InnertubeObjects
{
    class Video
    {
    public:
        bool isLive;
        InnertubeString lengthText;
        VideoOwner owner;
        InnertubeString publishedTimeText;
        InnertubeString shortViewCountText;
        VideoThumbnail thumbnail;
        InnertubeString title;
        QString videoId;
        InnertubeString viewCountText;

        Video(const QJsonObject& videoRenderer, bool isGridVideo)
        {
            isLive = videoRenderer.contains("badges")
                    ? videoRenderer["badges"].toArray()[0].toObject()["metadataBadgeRenderer"].toObject()["style"].toString() == "BADGE_STYLE_TYPE_LIVE_NOW"
                    : false;

            if (!isLive) // lengthText and publishedTimeText do not exist for live videos
            {
                if (isGridVideo)
                {
                    for (auto&& v : videoRenderer["thumbnailOverlays"].toArray())
                    {
                        QJsonObject timeStatus = v.toObject()["thumbnailOverlayTimeStatusRenderer"].toObject();
                        if (timeStatus.isEmpty()) continue;
                        lengthText = InnertubeString(timeStatus["text"]);
                    }
                }
                else
                {
                    lengthText = InnertubeString(videoRenderer["lengthText"]);
                }

                publishedTimeText = InnertubeString(videoRenderer["publishedTimeText"]);
            }

            videoId = videoRenderer["videoId"].toString();
            owner = isGridVideo
                    ? VideoOwner(videoRenderer["shortBylineText"], videoRenderer["channelThumbnail"], true)
                    : VideoOwner(videoRenderer["ownerText"], videoRenderer["channelThumbnailSupportedRenderers"], false);
            shortViewCountText = InnertubeString(videoRenderer["shortViewCountText"]);
            title = InnertubeString(videoRenderer["title"]);
            viewCountText = InnertubeString(videoRenderer["viewCountText"]);
            thumbnail = VideoThumbnail(videoId);
        }
    };
}

#endif // VIDEO_H
