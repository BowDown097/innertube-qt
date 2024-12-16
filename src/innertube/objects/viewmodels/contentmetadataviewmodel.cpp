#include "contentmetadataviewmodel.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    ContentMetadataViewModel::ContentMetadataViewModel(const QJsonValue& contentMetadataViewModel)
        : delimiter(contentMetadataViewModel["delimiter"].toString())
    {
        const QJsonArray metadataRowsJson = contentMetadataViewModel["metadataRows"].toArray();
        for (const QJsonValue& row : metadataRowsJson)
        {
            const QJsonArray metadataParts = row["metadataParts"].toArray();
            QList<DynamicText> textParts;
            textParts.reserve(metadataParts.size());
            for (const QJsonValue& part : metadataParts)
                textParts.append(DynamicText(part["text"]));
            metadataRows.append(textParts);
        }
    }
}
