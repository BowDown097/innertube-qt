#include "responsiveimage.h"
#include <QApplication>
#include <QJsonArray>
#include <QScreen>

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
        if (isEmpty())
            return nullptr;

        qreal targetWidth = target.width();
        if (QScreen* screen = qApp->primaryScreen())
            if (qreal dpr = screen->devicePixelRatio(); dpr > 1)
                targetWidth *= dpr;

        if (auto it = std::find_if(begin(), end(), [=](const GenericThumbnail& t) { return t.width >= targetWidth; }); it != end())
            return &(*it);
        if (auto rit = std::find_if(rbegin(), rend(), [=](const GenericThumbnail& t) { return t.width > 0; }); rit != rend())
            return &(*rit);
        return &front();
    }
}
