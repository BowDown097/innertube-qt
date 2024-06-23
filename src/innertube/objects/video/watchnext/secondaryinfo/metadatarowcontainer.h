#pragma once
#include "metadatarow.h"

namespace InnertubeObjects
{
    struct MetadataRowContainer
    {
        int collapsedItemCount{};
        QList<MetadataRow> rows;

        MetadataRowContainer() = default;
        explicit MetadataRowContainer(const QJsonValue& metadataRowContainerRenderer);
    };
}
