#include "responsiveimage.h"
#include <QJsonArray>
#include <QSize>

namespace InnertubeObjects
{
    ResponsiveImage::ResponsiveImage(const QJsonValue& thumbnails)
    {
        const QJsonArray arr = thumbnails.toArray();
        for (const QJsonValue& v : arr)
            append(GenericThumbnail(v));
    }

    const GenericThumbnail& ResponsiveImage::bestQuality() const
    {
        return *std::ranges::max_element(*this, [](const GenericThumbnail& a, const GenericThumbnail& b) {
            return a.height < b.height;
        });
    }

    const GenericThumbnail& ResponsiveImage::recommendedQuality(const QSize& target) const
    {
        return *std::ranges::min_element(*this, [&target](const GenericThumbnail& a, const GenericThumbnail& b) {
            return std::abs(a.width - target.width()) < std::abs(b.width - target.width());
        });
    }
}
