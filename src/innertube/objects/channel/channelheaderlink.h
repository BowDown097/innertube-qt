#ifndef CHANNELHEADERLINK_H
#define CHANNELHEADERLINK_H
#include <QJsonValue>

namespace InnertubeObjects
{
    struct ChannelHeaderLink
    {
        QString icon;
        QJsonValue navigationEndpoint;
        QString title;

        explicit ChannelHeaderLink(const QJsonValue& linkRenderer)
            : icon(linkRenderer["icon"]["thumbnails"][0]["url"].toString()),
              navigationEndpoint(linkRenderer["navigationEndpoint"]),
              title(linkRenderer["title"]["simpleText"].toString()) {}
    };
}

#endif // CHANNELHEADERLINK_H
