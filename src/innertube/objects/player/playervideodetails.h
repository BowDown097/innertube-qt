#ifndef PLAYERVIDEODETAILS_H
#define PLAYERVIDEODETAILS_H
#include "innertube/objects/genericthumbnail.h"
#include <QList>

namespace InnertubeObjects
{
    class PlayerVideoDetails
    {
    public:
        bool allowRatings = false;
        QString author;
        QString channelId;
        QStringList keywords;
        bool isCrawlable = false;
        bool isLive = false;
        bool isLiveContent = false;
        bool isLiveDvrEnabled = false;
        bool isLowLatencyLiveStream = false;
        bool isOwnerViewing = false;
        bool isPrivate = false;
        bool isUnpluggedCorpus = false;
        QString latencyClass;
        QString lengthSeconds;
        int liveChunkReadahead = 0;
        QString shortDescription;
        QList<GenericThumbnail> thumbnails;
        QString title;
        QString viewCount;
        QString videoId;

        PlayerVideoDetails() = default;
        explicit PlayerVideoDetails(const QJsonValue& videoDetails);
    };
}

#endif // PLAYERVIDEODETAILS_H
