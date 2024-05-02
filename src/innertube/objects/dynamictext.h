#pragma once
#include <QJsonValue>

namespace InnertubeObjects
{
    struct DynamicText
    {
        QJsonValue attachmentRuns;
        QJsonValue commandRuns;
        QString content;
        QJsonValue decorationRuns;
        QJsonValue styleRuns;

        DynamicText() = default;
        explicit DynamicText(const QJsonValue& textObject)
            : attachmentRuns(textObject["attachmentRuns"]),
              commandRuns(textObject["commandRuns"]),
              content(textObject["content"].toString()),
              decorationRuns(textObject["decorationRuns"]),
              styleRuns(textObject["styleRuns"]) {}
    };
}
