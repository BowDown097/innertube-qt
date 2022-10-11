#ifndef PLAYERVIDEODETAILS_H
#define PLAYERVIDEODETAILS_H
#include "../genericthumbnail.h"
#include <QList>
#include <QJsonObject>

namespace InnertubeObjects
{
    class PlayerVideoDetails
    {
    public:
        bool allowRatings;
        QString author;
        QString channelId;
        QList<QString> keywords;
        bool isCrawlable;
        bool isLive;
        bool isLiveContent;
        bool isLiveDvrEnabled;
        bool isLowLatencyLiveStream;
        bool isOwnerViewing;
        bool isPrivate;
        bool isUnpluggedCorpus;
        QString latencyClass;
        QString lengthSeconds;
        int liveChunkReadahead;
        QString shortDescription;
        QList<GenericThumbnail> thumbnails;
        QString title;
        QString viewCount;
        QString videoId;

        PlayerVideoDetails() {}
        explicit PlayerVideoDetails(const QJsonObject& videoDetails) : allowRatings(videoDetails["allowRatings"].toBool()),
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
    };
}

#endif // PLAYERVIDEODETAILS_H
