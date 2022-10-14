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
        explicit PlayerVideoDetails(const QJsonObject& videoDetails);
    };
}

#endif // PLAYERVIDEODETAILS_H
