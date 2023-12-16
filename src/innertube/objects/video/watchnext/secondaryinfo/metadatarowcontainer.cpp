#include "metadatarowcontainer.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    MetadataRowContainer::MetadataRowContainer(const QJsonValue& metadataRowContainerRenderer)
        : collapsedItemCount(metadataRowContainerRenderer["collapsedItemCount"].toInt())
    {
        const QJsonArray rowsJson = metadataRowContainerRenderer["rows"].toArray();
        for (const QJsonValue& v : rowsJson)
            rows.append(MetadataRow(v["metadataRowRenderer"]));
    }
}
