#include "carouselitemviewmodel.h"

namespace InnertubeObjects
{
    CarouselItemViewModel::CarouselItemViewModel(const QJsonValue& carouselItemViewModel)
        : itemType(carouselItemViewModel["itemType"].toString())
    {
        const QJsonValue carouselItemJson = carouselItemViewModel["carouselItem"];
        if (const QJsonValue textCarouselItem = carouselItemJson["textCarouselItemViewModel"]; textCarouselItem.isObject())
            carouselItem = TextCarouselItemViewModel(textCarouselItem);
    }
}
