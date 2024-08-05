#include "responsiveimage.h"
#include <QJsonArray>
#include <QSize>

namespace InnertubeObjects
{
    ResponsiveImage::ResponsiveImage(const QJsonValue& thumbnails)
    {
        const QJsonArray thumbnailsArr = thumbnails.toArray();
        for (const QJsonValue& v : thumbnailsArr)
            append(GenericThumbnail(v));
    }

    std::optional<std::reference_wrapper<const GenericThumbnail>> ResponsiveImage::bestQuality() const
    {
        auto it = std::ranges::max_element(*this, [](const auto& a, const auto& b) { return a.height < b.height; });
        if (it == end())
            return std::nullopt;
        else
            return *it;
    }

    std::optional<std::reference_wrapper<const GenericThumbnail>>
    ResponsiveImage::recommendedQuality(const QSize& target) const
    {
        auto it = std::ranges::max_element(*this, [target](const GenericThumbnail& a, const GenericThumbnail& b) {
            return std::abs(a.width - target.width()) < std::abs(b.width - target.width());
        });
        if (it == end())
            return std::nullopt;
        else
            return *it;
    }
}
