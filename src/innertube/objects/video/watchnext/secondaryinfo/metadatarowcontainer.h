#ifndef METADATAROWCONTAINER_H
#define METADATAROWCONTAINER_H
#include "metadatarow.h"

namespace InnertubeObjects
{
    struct MetadataRowContainer
    {
        int collapsedItemCount;
        QList<MetadataRow> rows;

        MetadataRowContainer() = default;
        explicit MetadataRowContainer(const QJsonValue& metadataRowContainerRenderer);
    };
}

#endif // METADATAROWCONTAINER_H
