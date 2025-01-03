#pragma once
#include "basevideo.h"
#include "channelthumbnailwithlink.h"
#include "innertube/objects/channel/metadatabadge.h"
#include "innertube/objects/images/movingthumbnail.h"
#include "innertube/objects/items/togglebutton.h"
#include "innertube/objects/viewmodels/decoratedavatarviewmodel.h"
#include "metadatasnippet.h"
#include "upcomingeventdata.h"
#include <QTime>

namespace InnertubeObjects
{
    struct Video : BaseVideo
    {
        DecoratedAvatarViewModel avatar;
        QList<MetadataBadge> badges;
        QList<ToggleButton> buttons;
        ChannelThumbnailWithLink channelThumbnailSupportedRenderers;
        InnertubeString descriptionSnippet;
        QList<MetadataSnippet> detailedMetadataSnippets;
        QJsonValue inlinePlaybackEndpoint;
        bool isWatched{};
        QList<MetadataBadge> ownerBadges;
        InnertubeString ownerText;
        InnertubeString publishedTimeText;
        MovingThumbnail richThumbnail;
        QString searchVideoResultEntityKey;
        InnertubeString shortViewCountText;
        bool showActionMenu{};
        std::optional<UpcomingEventData> upcomingEventData;
        InnertubeString viewCountText;

        Video() = default;
        explicit Video(const QJsonValue& videoRenderer);

        bool isLive() const;

        // reels can still be of this type and not of the Reel type. blame innertube
        bool isReel() const;

        QString ownerId() const;

        /**
         * @return Upcoming event start time, or else publishedTimeText.
         */
        QString publishedTimeDisplay() const;
    };
}
