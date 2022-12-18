#include "playervideodetails.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    PlayerVideoDetails::PlayerVideoDetails(const QJsonValue& videoDetails)
        : allowRatings(videoDetails["allowRatings"].toBool()),
          author(videoDetails["author"].toString()),
          channelId(videoDetails["channelId"].toString()),
          isCrawlable(videoDetails["isCrawlable"].toBool()),
          isLive(videoDetails["isLive"].toBool()),
          isLiveContent(videoDetails["isLiveContent"].toBool()),
          isLiveDvrEnabled(videoDetails["isLiveDvrEnabled"].toBool()),
          isLowLatencyLiveStream(videoDetails["isLowLatencyLiveStream"].toBool()),
          isOwnerViewing(videoDetails["isOwnerViewing"].toBool()),
          isPrivate(videoDetails["isPrivate"].toBool()),
          isUnpluggedCorpus(videoDetails["isUnpluggedCorpus"].toBool()),
          latencyClass(videoDetails["latencyClass"].toString()),
          lengthSeconds(videoDetails["lengthSeconds"].toString()),
          liveChunkReadahead(videoDetails["liveChunkReadahead"].toInt()),
          shortDescription(videoDetails["shortDescription"].toString()),
          title(videoDetails["title"].toString()),
          viewCount(videoDetails["viewCount"].toString()),
          videoId(videoDetails["videoId"].toString())
    {
        const QJsonArray keywordsJson = videoDetails["keywords"].toArray();
        const QJsonArray thumbnailsJson = videoDetails["thumbnail"]["thumbnails"].toArray();
        for (const QJsonValue& v : keywordsJson)
            keywords.append(v.toString());
        for (const QJsonValue& v : thumbnailsJson)
            thumbnails.append(GenericThumbnail(v["height"].toInt(), "https:" + v["url"].toString(), v["width"].toInt()));
    }
}
