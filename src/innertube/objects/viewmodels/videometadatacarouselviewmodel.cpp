#include "videometadatacarouselviewmodel.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    VideoMetadataCarouselViewModel::VideoMetadataCarouselViewModel(const QJsonValue& videoMetadataCarouselViewModel)
    {
        const QJsonArray carouselItemsJson = videoMetadataCarouselViewModel["carouselItems"].toArray();
        for (const QJsonValue& carouselItem : carouselItemsJson)
            carouselItems.append(CarouselItemViewModel(carouselItem["carouselItemViewModel"]));

        const QJsonArray carouselTitlesJson = videoMetadataCarouselViewModel["carouselTitles"].toArray();
        for (const QJsonValue& carouselTitle : carouselTitlesJson)
            carouselTitles.append(CarouselTitleViewModel(carouselTitle["carouselTitleViewModel"]));
    }
}
