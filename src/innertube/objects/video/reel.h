#ifndef REEL_H
#define REEL_H
#include "innertube/objects/genericthumbnail.h"
#include "innertube/objects/innertubestring.h"
#include "videoowner.h"

namespace InnertubeObjects
{
    struct Reel
    {
        QString accessibilityLabel;
        QString headline;
        VideoOwner owner;
        QString style;
        QList<GenericThumbnail> thumbnails;
        QString videoId;
        QString videoType;
        InnertubeString viewCountText;

        explicit Reel(const QJsonValue& reelItemRenderer);
    };
}

#endif // REEL_H
