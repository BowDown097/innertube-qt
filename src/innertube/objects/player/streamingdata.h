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

        StreamingData() = default;
        explicit StreamingData(const QJsonValue& streamingData);
    };
}

#endif // STREAMINGDATA_H
