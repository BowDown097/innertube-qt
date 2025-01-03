#pragma once
#include "innertube/objects/images/imagewithcolorpalette.h"
#include "innertube/objects/items/menu/menu.h"
#include "thumbnail_overlays/thumbnailoverlayendorsement.h"
#include "thumbnail_overlays/thumbnailoverlayinlineunplayable.h"
#include "thumbnail_overlays/thumbnailoverlayloadingpreview.h"
#include "thumbnail_overlays/thumbnailoverlaynowplaying.h"
#include "thumbnail_overlays/thumbnailoverlayresumeplayback.h"
#include "thumbnail_overlays/thumbnailoverlaytimestatus.h"
#include "thumbnail_overlays/thumbnailoverlaytogglebutton.h"
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

    struct BaseVideo
    {
        InnertubeString lengthText;
        InnertubeString longBylineText;
        Menu menu;
        QJsonValue navigationEndpoint;
        InnertubeString shortBylineText;
        ImageWithColorPalette thumbnail;
        QList<ThumbnailOverlay> thumbnailOverlays;
        InnertubeString title;
        QString videoId;

        BaseVideo() = default;
        explicit BaseVideo(const QJsonValue& renderer);

        QTime length() const;

        /**
         * @return ThumbnailOverlayTimeStatus text, or else lengthText.
         */
        const InnertubeString& lengthDisplay() const;
    };
}
