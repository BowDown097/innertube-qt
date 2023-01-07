#include "channelheader.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    ChannelHeader::ChannelHeader(const QJsonValue& headerRenderer)
        : channelHandleText(headerRenderer["channelHandleText"]),
          channelId(headerRenderer["channelId"].toString()),
          subscribeButton(headerRenderer["subscribeButton"]["subscribeButtonRenderer"]),
          subscriberCountText(headerRenderer["subscriberCountText"]),
          title(headerRenderer["title"].toString()),
          videosCountText(headerRenderer["videosCountText"])
    {
        const QJsonArray avatarJson = headerRenderer["avatar"]["thumbnails"].toArray();
        for (const QJsonValue& v : avatarJson)
            avatar.append(GenericThumbnail(v));

        const QJsonArray bannerJson = headerRenderer["banner"]["thumbnails"].toArray();
        for (const QJsonValue& v : bannerJson)
            banner.append(GenericThumbnail(v));

        const QJsonArray mobileBannerJson = headerRenderer["mobileBanner"]["thumbnails"].toArray();
        for (const QJsonValue& v : mobileBannerJson)
            mobileBanner.append(GenericThumbnail(v));

        const QJsonArray primaryLinksJson = headerRenderer["headerLinks"]["channelHeaderLinksRenderer"]["primaryLinks"].toArray();
        for (const QJsonValue& v : primaryLinksJson)
            primaryLinks.append(ChannelHeaderLink(v));

        const QJsonArray secondaryLinksJson = headerRenderer["headerLinks"]["channelHeaderLinksRenderer"]["secondaryLinks"].toArray();
        for (const QJsonValue& v : secondaryLinksJson)
            secondaryLinks.append(ChannelHeaderLink(v));

        const QJsonArray tvBannerJson = headerRenderer["tvBanner"].toArray();
        for (const QJsonValue& v : tvBannerJson)
            tvBanner.append(GenericThumbnail(v));
    }
}
