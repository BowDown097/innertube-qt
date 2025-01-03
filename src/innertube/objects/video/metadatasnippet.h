#pragma once
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    struct MetadataSnippet
    {
        bool maxOneLine{};
        InnertubeString snippetHoverText;
        InnertubeString snippetText;

        MetadataSnippet() = default;
        explicit MetadataSnippet(const QJsonValue& data)
            : maxOneLine(data["maxOneLine"].toBool()),
              snippetHoverText(data["snippetHoverText"]),
              snippetText(data["snippetText"]) {}
    };
}
