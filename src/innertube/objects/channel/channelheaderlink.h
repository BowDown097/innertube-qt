#ifndef CHANNELHEADERLINK_H
#define CHANNELHEADERLINK_H
#include "innertube/objects/navigation/navigationendpoint.h"

namespace InnertubeObjects
{
    class ChannelHeaderLink
    {
    public:
        QString icon;
        NavigationEndpoint navigationEndpoint;
        QString title;
        explicit ChannelHeaderLink(const QJsonValue& linkRenderer)
            : icon(linkRenderer["icon"]["thumbnails"][0]["url"].toString()),
              navigationEndpoint(linkRenderer["navigationEndpoint"]),
              title(linkRenderer["title"]["simpleText"].toString()) {}
    };
}

#endif // CHANNELHEADERLINK_H
