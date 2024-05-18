#pragma once
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    struct MetadataRow
    {
        QList<InnertubeString> contents;
        InnertubeString title;

        MetadataRow() = default;
        explicit MetadataRow(const QJsonValue& metadataRowRenderer);
    };
}
