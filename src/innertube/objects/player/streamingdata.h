#ifndef STREAMINGDATA_H
#define STREAMINGDATA_H
#include "streamingformat.h"

namespace InnertubeObjects
{
    class StreamingData
    {
    public:
        QList<StreamingFormat> adaptiveFormats;
        QString dashManifestUrl;
        QString expiresInSeconds;
        QList<StreamingFormat> formats;
        QString hlsManifestUrl;

        StreamingData() {}
        explicit StreamingData(const QJsonObject& streamingData);
    };
}

#endif // STREAMINGDATA_H
