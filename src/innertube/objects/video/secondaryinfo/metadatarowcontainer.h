#ifndef METADATAROWCONTAINER_H
#define METADATAROWCONTAINER_H
#include "metadatarow.h"

namespace InnertubeObjects
{
    class MetadataRowContainer
    {
    public:
        int collapsedItemCount;
        QList<MetadataRow> rows;

        MetadataRowContainer() {}
        explicit MetadataRowContainer(const QJsonValue& metadataRowContainerRenderer);
    };
}

#endif // METADATAROWCONTAINER_H
