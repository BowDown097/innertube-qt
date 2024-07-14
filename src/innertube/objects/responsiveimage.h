#pragma once
#include "genericthumbnail.h"
#include <optional>

namespace InnertubeObjects
{
    struct ResponsiveImage : QList<GenericThumbnail>
    {
        ResponsiveImage() = default;
        explicit ResponsiveImage(const QJsonValue& thumbnails);
        std::optional<std::reference_wrapper<const GenericThumbnail>> bestQuality() const;
        std::optional<std::reference_wrapper<const GenericThumbnail>> recommendedQuality(const QSize& target) const;
    };
}
