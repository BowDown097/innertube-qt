#pragma once
#include "innertube/objects/dynamictext.h"

namespace InnertubeObjects
{
    struct ContentMetadataViewModel
    {
        QString delimiter;
        QList<QList<DynamicText>> metadataRows;

        ContentMetadataViewModel() = default;
        explicit ContentMetadataViewModel(const QJsonValue& contentMetadataViewModel);
    };
}
