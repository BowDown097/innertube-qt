#pragma once
#include "innertubestring.h"

namespace InnertubeObjects
{
    struct CompactLink
    {
        QString iconType;
        QJsonValue navigationEndpoint;
        InnertubeString title;

        explicit CompactLink(const QJsonValue& compactLinkRenderer)
            : iconType(compactLinkRenderer["icon"]["iconType"].toString()),
              navigationEndpoint(compactLinkRenderer["navigationEndpoint"]),
              title(compactLinkRenderer["title"]) {}
    };
}
