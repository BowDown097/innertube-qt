#pragma once
#include "badgeviewmodel.h"
#include "innertube/objects/dynamictext.h"

namespace InnertubeObjects
{
    struct ContentMetadataViewModel
    {
        QString delimiter;
        QList<std::variant<QList<BadgeViewModel>, QList<DynamicText>>> metadataRows;

        ContentMetadataViewModel() = default;
        explicit ContentMetadataViewModel(const QJsonValue& contentMetadataViewModel);
    };
}
