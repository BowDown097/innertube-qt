#pragma once
#include "innertubestring.h"

namespace InnertubeObjects
{
    struct DynamicText
    {
        QJsonValue attachmentRuns;
        QJsonValue commandRuns;
        QString content;
        QJsonValue decorationRuns;
        QJsonValue paragraphStyleRuns;
        QJsonValue styleRuns;

        DynamicText() = default;
        explicit DynamicText(const QJsonValue& textObject)
            : attachmentRuns(textObject["attachmentRuns"]),
              commandRuns(textObject["commandRuns"]),
              content(textObject["content"].toString()),
              decorationRuns(textObject["decorationRuns"]),
              paragraphStyleRuns(textObject["paragraphStyleRuns"]),
              styleRuns(textObject["styleRuns"]) {}

        InnertubeString unattribute() const;
    };
}
