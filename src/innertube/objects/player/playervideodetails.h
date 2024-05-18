#pragma once
#include "innertube/objects/responsiveimage.h"

namespace InnertubeObjects
{
    struct PlayerVideoDetails
    {
        bool allowRatings;
        QString author;
        QString channelId;
        bool isCrawlable;
        bool isLive;
        bool isLiveContent;
        bool isLiveDvrEnabled;
        bool isLowLatencyLiveStream;
        bool isOwnerViewing;
        bool isPrivate;
        bool isUnpluggedCorpus;
        bool isUpcoming;
        QStringList keywords;
        QString latencyClass;
        QString lengthSeconds;
        int liveChunkReadahead;
        QString shortDescription;
        ResponsiveImage thumbnail;
        QString title;
        QString viewCount;
        QString videoId;

        PlayerVideoDetails() = default;
        explicit PlayerVideoDetails(const QJsonValue& videoDetails);
    };
}
