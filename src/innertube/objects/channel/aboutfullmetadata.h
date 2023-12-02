#ifndef ABOUTFULLMETADATA_H
#define ABOUTFULLMETADATA_H
#include "channelheaderlink.h"
#include "innertube/objects/genericthumbnail.h"
#include "innertube/objects/items/button.h"

namespace InnertubeObjects
{
    struct AboutFullMetadata
    {
        QList<Button> actionButtons;
        QList<GenericThumbnail> avatars;
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

#endif // ABOUTFULLMETADATA_H
