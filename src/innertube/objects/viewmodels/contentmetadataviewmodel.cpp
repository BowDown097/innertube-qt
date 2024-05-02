#include "contentmetadataviewmodel.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    ContentMetadataViewModel::ContentMetadataViewModel(const QJsonValue& contentMetadataViewModel)
        : delimiter(contentMetadataViewModel["delimiter"].toString())
    {
        const QJsonArray metaRows = contentMetadataViewModel["metadataRows"].toArray();
        for (const QJsonValue& row : metaRows)
        {
            const QJsonArray metaParts = row["metadataParts"].toArray();
            QStringList textParts;
            textParts.reserve(metaParts.size());
            for (const QJsonValue& part : metaParts)
                textParts.append(part["text"]["content"].toString());
            metadataRows.append(textParts);
        }
    }
}
