#include "contentmetadataviewmodel.h"
#include <QJsonArray>
#include <QJsonObject>

namespace InnertubeObjects
{
    ContentMetadataRow::ContentMetadataRow(const QJsonValue& metadataRow)
        : contentType(metadataRow["lockupContentMetadataRowExtension"]["contentType"].toString()),
          isSpacerRow(metadataRow["isSpacerRow"].toBool())
    {
        if (const QJsonValue metadataPartsJson = metadataRow["metadataParts"]; metadataPartsJson.isArray())
        {
            const QJsonArray metadataPartsArr = metadataPartsJson.toArray();
            QList<DynamicText> metadataParts;
            metadataParts.reserve(metadataPartsArr.size());
            for (const QJsonValue& metadataPart : metadataPartsArr)
                metadataParts.append(DynamicText(metadataPart["text"]));
            content = std::move(metadataParts);
        }
        else if (const QJsonValue badgesJson = metadataRow["badges"]; badgesJson.isArray())
        {
            const QJsonArray badgesArr = badgesJson.toArray();
            QList<BadgeViewModel> badges;
            badges.reserve(badgesArr.size());
            for (const QJsonValue& badge : badgesArr)
                badges.append(BadgeViewModel(badge["badgeViewModel"]));
            content = std::move(badges);
        }
    }

    ContentMetadataViewModel::ContentMetadataViewModel(const QJsonValue& contentMetadataViewModel)
        : delimiter(contentMetadataViewModel["delimiter"].toString())
    {
        const QJsonArray metadataRowsJson = contentMetadataViewModel["metadataRows"].toArray();
        for (const QJsonValue& metadataRow : metadataRowsJson)
            metadataRows.emplaceBack(metadataRow);
    }
}
