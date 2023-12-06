#ifndef RESPONSIVEIMAGE_H
#define RESPONSIVEIMAGE_H
#include "genericthumbnail.h"

namespace InnertubeObjects
{
    struct ResponsiveImage : QList<GenericThumbnail>
    {
        ResponsiveImage() = default;
        explicit ResponsiveImage(const QJsonValue& thumbnails);
        const GenericThumbnail& bestQuality() const;
        const GenericThumbnail& recommendedQuality(const QSize& target) const;
    };
}

#endif // RESPONSIVEIMAGE_H
