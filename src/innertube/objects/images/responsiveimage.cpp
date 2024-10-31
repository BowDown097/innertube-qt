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

    const GenericThumbnail* ResponsiveImage::bestQuality() const
    {
        auto heightFilter = [](const GenericThumbnail& a) { return a.height; };
        auto it = std::ranges::max_element(*this, std::less(), heightFilter);
        if (it != end())
            return &(*it);
        else
            return nullptr;
    }

    const GenericThumbnail* ResponsiveImage::recommendedQuality(const QSize& target) const
    {
        auto absWidth = [target](const GenericThumbnail& a) { return std::abs(a.width - target.width()); };
        auto it = std::ranges::max_element(*this, std::less(), absWidth);
        if (it != end())
            return &(*it);
        else
            return nullptr;
    }
}
