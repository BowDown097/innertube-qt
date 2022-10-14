#include "playervideodetails.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    PlayerVideoDetails::PlayerVideoDetails(const QJsonObject& videoDetails) : allowRatings(videoDetails["allowRatings"].toBool()),
        author(videoDetails["author"].toString()), channelId(videoDetails["channelId"].toString()),
        isCrawlable(videoDetails["isCrawlable"].toBool()), isLive(videoDetails["isLive"].toBool()),
        isLiveContent(videoDetails["isLiveContent"].toBool()), isLiveDvrEnabled(videoDetails["isLiveDvrEnabled"].toBool()),
        isLowLatencyLiveStream(videoDetails["isLowLatencyLiveStream"].toBool()), isOwnerViewing(videoDetails["isOwnerViewing"].toBool()),
        isPrivate(videoDetails["isPrivate"].toBool()), isUnpluggedCorpus(videoDetails["isUnpluggedCorpus"].toBool()),
        latencyClass(videoDetails["latencyClass"].toString()), lengthSeconds(videoDetails["lengthSeconds"].toString()),
        liveChunkReadahead(videoDetails["liveChunkReadahead"].toInt()), shortDescription(videoDetails["shortDescription"].toString()),
        title(videoDetails["title"].toString()), viewCount(videoDetails["viewCount"].toString()), videoId(videoDetails["videoId"].toString())
    {
        for (auto&& v : videoDetails["keywords"].toArray())
            keywords.append(v.toString());

        for (auto&& v : videoDetails["thumbnail"].toObject()["thumbnails"].toArray())
        {
            const QJsonObject& o = v.toObject();
            thumbnails.append(GenericThumbnail(o["height"].toInt(), o["url"].toString(), o["width"].toInt()));
        }
    }
}
