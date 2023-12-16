#include "metadatarow.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    MetadataRow::MetadataRow(const QJsonValue& metadataRowRenderer)
        : title(metadataRowRenderer["title"])
    {
        const QJsonArray contentsJson = metadataRowRenderer["contents"].toArray();
        for (const QJsonValue& v : contentsJson)
            contents.append(InnertubeString(v));
    }
}
