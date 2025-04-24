#pragma once
#include "buttonviewmodel.h"

namespace InnertubeObjects
{
    struct TextCarouselItemViewModel
    {
        ButtonViewModel button;
        QString iconName;
        QJsonValue onTap;
        QString text;

        TextCarouselItemViewModel() = default;
        explicit TextCarouselItemViewModel(const QJsonValue& textCarouselItemViewModel)
            : button(textCarouselItemViewModel["button"]["buttonViewModel"]),
              iconName(textCarouselItemViewModel["iconName"].toString()),
              onTap(textCarouselItemViewModel["onTap"]),
              text(textCarouselItemViewModel["text"].toString()) {}
    };
}
