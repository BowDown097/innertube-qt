#include "contentmetadataviewmodel.h"
#include <QJsonArray>
#include <QJsonObject>

namespace InnertubeObjects
{
    ContentMetadataViewModel::ContentMetadataViewModel(const QJsonValue& contentMetadataViewModel)
        : delimiter(contentMetadataViewModel["delimiter"].toString())
    {
        const QJsonArray metadataRowsJson = contentMetadataViewModel["metadataRows"].toArray();
        for (const QJsonValue& row : metadataRowsJson)
        {
            const QJsonObject obj = row.toObject();
            const QString key = obj.begin().key();

            if (key == "metadataParts")
            {
                const QJsonArray metadataPartsJson = obj.begin()->toArray();
                QList<DynamicText> metadataParts;
                metadataParts.reserve(metadataPartsJson.size());
                for (const QJsonValue& metadataPart : metadataPartsJson)
                    metadataParts.append(DynamicText(metadataPart["text"]));
                metadataRows.append(metadataParts);
            }
            else if (key == "badges")
            {
                const QJsonArray badgesJson = obj.begin()->toArray();
                QList<BadgeViewModel> badges;
                badges.reserve(badgesJson.size());
                for (const QJsonValue& badge : badgesJson)
                    badges.append(BadgeViewModel(badge["badgeViewModel"]));
                metadataRows.append(badges);
            }
        }
    }
}
