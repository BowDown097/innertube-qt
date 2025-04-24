#pragma once
#include "carouselitemviewmodel.h"
#include "carouseltitleviewmodel.h"

namespace InnertubeObjects
{
    struct VideoMetadataCarouselViewModel
    {
        QList<CarouselItemViewModel> carouselItems;
        QList<CarouselTitleViewModel> carouselTitles;

        VideoMetadataCarouselViewModel() = default;
        explicit VideoMetadataCarouselViewModel(const QJsonValue& videoMetadataCarouselViewModel);
    };
}
