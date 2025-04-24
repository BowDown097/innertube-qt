#pragma once
#include "textcarouselitemviewmodel.h"

namespace InnertubeObjects
{
    struct CarouselItemViewModel
    {
        std::variant<TextCarouselItemViewModel> carouselItem;
        QString itemType;

        CarouselItemViewModel() = default;
        explicit CarouselItemViewModel(const QJsonValue& carouselItemViewModel);
    };
}
