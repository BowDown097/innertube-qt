#ifndef COMPACTLINK_H
#define COMPACTLINK_H
#include "innertubestring.h"

namespace InnertubeObjects
{
    class CompactLink
    {
    public:
        QString iconType;
        QJsonValue navigationEndpoint;
        InnertubeString title;

        explicit CompactLink(const QJsonValue& compactLinkRenderer)
            : iconType(compactLinkRenderer["icon"]["iconType"].toString()),
              navigationEndpoint(compactLinkRenderer["navigationEndpoint"]),
              title(compactLinkRenderer["title"]) {}
    };
}

#endif // COMPACTLINK_H
