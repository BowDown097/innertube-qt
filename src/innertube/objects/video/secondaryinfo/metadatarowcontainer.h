#ifndef METADATAROWCONTAINER_H
#define METADATAROWCONTAINER_H
#include "metadatarow.h"

namespace InnertubeObjects
{
    class MetadataRowContainer
    {
    public:
        int collapsedItemCount = 0;
        QList<MetadataRow> rows;

        MetadataRowContainer() = default;
        explicit MetadataRowContainer(const QJsonValue& metadataRowContainerRenderer);
    };
}

#endif // METADATAROWCONTAINER_H
