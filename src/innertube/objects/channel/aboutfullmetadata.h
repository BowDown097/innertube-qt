#pragma once
#include "channelheaderlink.h"
#include "innertube/objects/items/button.h"
#include "innertube/objects/responsiveimage.h"

namespace InnertubeObjects
{
    struct AboutFullMetadata
    {
        QList<Button> actionButtons;
        ResponsiveImage avatar;
        bool bypassBusinessEmailCaptcha;
        QString canonicalChannelUrl;
        QString channelId;
        QString country;
        InnertubeString countryLabel;
        QString description;
        InnertubeString descriptionLabel;
        InnertubeString detailsLabel;
        InnertubeString joinedDateText;
        QList<ChannelHeaderLink> primaryLinks;
        InnertubeString primaryLinksLabel;
        bool showDescription;
        InnertubeString statsLabel;
        QString title;
        QString viewCountText;

        explicit AboutFullMetadata(const QJsonValue& renderer);
    };
}
