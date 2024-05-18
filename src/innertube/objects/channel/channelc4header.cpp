#include "channelc4header.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    ChannelC4Header::ChannelC4Header(const QJsonValue& headerRenderer)
        : avatar(headerRenderer["avatar"]["thumbnails"]),
          banner(headerRenderer["banner"]["thumbnails"]),
          channelHandleText(headerRenderer["channelHandleText"]),
          channelId(headerRenderer["channelId"].toString()),
          mobileBanner(headerRenderer["mobileBanner"]["thumbnails"]),
          subscribeButton(headerRenderer["subscribeButton"]["subscribeButtonRenderer"]),
          subscriberCountText(headerRenderer["subscriberCountText"]),
          title(headerRenderer["title"].toString()),
          tvBanner(headerRenderer["tvBanner"]),
          videosCountText(headerRenderer["videosCountText"])
    {
        const QJsonArray primaryLinksJson = headerRenderer["headerLinks"]["channelHeaderLinksRenderer"]["primaryLinks"].toArray();
        for (const QJsonValue& v : primaryLinksJson)
            primaryLinks.append(ChannelHeaderLink(v));

        const QJsonArray secondaryLinksJson = headerRenderer["headerLinks"]["channelHeaderLinksRenderer"]["secondaryLinks"].toArray();
        for (const QJsonValue& v : secondaryLinksJson)
            secondaryLinks.append(ChannelHeaderLink(v));
    }
}
