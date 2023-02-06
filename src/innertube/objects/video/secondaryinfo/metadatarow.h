#ifndef METADATAROW_H
#define METADATAROW_H
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    class MetadataRow
    {
    public:
        QList<InnertubeString> contents;
        InnertubeString title;

        MetadataRow() {}
        explicit MetadataRow(const QJsonValue& metadataRowRenderer);
    };
}

#endif // METADATAROW_H
