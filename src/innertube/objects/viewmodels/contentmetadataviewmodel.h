#pragma once
#include "badgeviewmodel.h"
#include "innertube/objects/dynamictext.h"

namespace InnertubeObjects
{
    struct ContentMetadataRow
    {
        std::variant<std::monostate, QList<BadgeViewModel>, QList<DynamicText>> content;
        QString contentType;
        bool isSpacerRow{};

        ContentMetadataRow() = default;
        explicit ContentMetadataRow(const QJsonValue& metadataRow);
    };

    struct ContentMetadataViewModel
    {
        QString delimiter;
        QList<ContentMetadataRow> metadataRows;

        ContentMetadataViewModel() = default;
        explicit ContentMetadataViewModel(const QJsonValue& contentMetadataViewModel);
    };
}
