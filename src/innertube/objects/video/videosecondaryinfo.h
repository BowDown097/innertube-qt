#ifndef VIDEOSECONDARYINFO_H
#define VIDEOSECONDARYINFO_H
#include "innertube/objects/genericthumbnail.h"
#include "innertube/objects/channel/subscribebutton.h"

namespace InnertubeObjects
{
    class VideoSecondaryInfo
    {
    public:
        QList<GenericThumbnail> channelIcons;
        InnertubeString channelName;
        InnertubeString description;
        SubscribeButton subscribeButton;
        InnertubeString subscriberCountText;

        VideoSecondaryInfo() {}
        explicit VideoSecondaryInfo(const QJsonValue& secondaryInfoRenderer);
    };
}

#endif // VIDEOSECONDARYINFO_H
