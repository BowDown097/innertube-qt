#ifndef VIDEOSECONDARYINFO_H
#define VIDEOSECONDARYINFO_H
#include "innertube/objects/genericthumbnail.h"
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    class VideoSecondaryInfo
    {
    public:
        QList<GenericThumbnail> channelIcons;
        QString channelId;
        InnertubeString channelName;
        InnertubeString description; // this will be more complex later for easy usage of timestamps, urls, etc.
        bool subscribed;
        InnertubeString subscriberCountText;
        bool subscriptionsEnabled;
        QString subscriptionType;

        VideoSecondaryInfo() {}
        explicit VideoSecondaryInfo(const QJsonValue& secondaryInfoRenderer);
    };
}

#endif // VIDEOSECONDARYINFO_H
