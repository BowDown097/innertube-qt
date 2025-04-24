#pragma once
#include "buttonviewmodel.h"

namespace InnertubeObjects
{
    struct CarouselTitleViewModel
    {
        ButtonViewModel nextButton;
        ButtonViewModel previousButton;
        QString title;

        CarouselTitleViewModel() = default;
        explicit CarouselTitleViewModel(const QJsonValue& carouselTitleViewModel)
            : nextButton(carouselTitleViewModel["nextButton"]["buttonViewModel"]),
              previousButton(carouselTitleViewModel["previousButton"]["buttonViewModel"]),
              title(carouselTitleViewModel["title"].toString()) {}
    };
}
