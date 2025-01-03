#pragma once
#include "channelthumbnailwithlink.h"
#include "innertube/objects/channel/metadatabadge.h"
#include "innertube/objects/images/imagewithcolorpalette.h"
#include "innertube/objects/images/movingthumbnail.h"
#include "innertube/objects/items/menu/menu.h"
#include "innertube/objects/items/togglebutton.h"
#include "innertube/objects/viewmodels/decoratedavatarviewmodel.h"
#include "metadatasnippet.h"
#include "thumbnail_overlays/thumbnailoverlayendorsement.h"
#include "thumbnail_overlays/thumbnailoverlayinlineunplayable.h"
#include "thumbnail_overlays/thumbnailoverlayloadingpreview.h"
#include "thumbnail_overlays/thumbnailoverlaynowplaying.h"
#include "thumbnail_overlays/thumbnailoverlayresumeplayback.h"
#include "thumbnail_overlays/thumbnailoverlaytimestatus.h"
#include "thumbnail_overlays/thumbnailoverlaytogglebutton.h"
#include "upcomingeventdata.h"
#include <QTime>

namespace InnertubeObjects
{
    using ThumbnailOverlay = std::variant<
        ThumbnailOverlayEndorsement,
        ThumbnailOverlayInlineUnplayable,
        ThumbnailOverlayLoadingPreview,
        ThumbnailOverlayNowPlaying,
        ThumbnailOverlayResumePlayback,
        ThumbnailOverlayTimeStatus,
        ThumbnailOverlayToggleButton>;

    struct Video
    {
        DecoratedAvatarViewModel avatar;
        QList<MetadataBadge> badges;
        QList<ToggleButton> buttons;
        ChannelThumbnailWithLink channelThumbnailSupportedRenderers;
        InnertubeString descriptionSnippet;
        QList<MetadataSnippet> detailedMetadataSnippets;
        QJsonValue inlinePlaybackEndpoint;
        bool isWatched{};
        InnertubeString lengthText;
        InnertubeString longBylineText;
        Menu menu;
        QJsonValue navigationEndpoint;
        QList<MetadataBadge> ownerBadges;
        InnertubeString ownerText;
        InnertubeString publishedTimeText;
        MovingThumbnail richThumbnail;
        QString searchVideoResultEntityKey;
        InnertubeString shortBylineText;
        InnertubeString shortViewCountText;
        bool showActionMenu{};
        ImageWithColorPalette thumbnail;
        QList<ThumbnailOverlay> thumbnailOverlays;
        InnertubeString title;
        std::optional<UpcomingEventData> upcomingEventData;
        QString videoId;
        InnertubeString viewCountText;

        Video() = default;
        explicit Video(const QJsonValue& videoRenderer);

        bool isLive() const;

        // reels can still be of this type and not of the Reel type. blame innertube
        bool isReel() const;

        QTime length() const;

        /**
         * @return ThumbnailOverlayTimeStatus text, or else lengthText.
         */
        const InnertubeString& lengthDisplay() const;

        QString ownerId() const;

        /**
         * @return Upcoming event start time, or else publishedTimeText.
         */
        QString publishedTimeDisplay() const;
    };
}
