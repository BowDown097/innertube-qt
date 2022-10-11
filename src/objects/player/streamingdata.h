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
        explicit StreamingData(const QJsonObject& streamingData) : dashManifestUrl(streamingData["dashManifestUrl"].toString()),
            expiresInSeconds(streamingData["expiresInSeconds"].toString()), hlsManifestUrl(streamingData["hlsManifestUrl"].toString())
        {
            for (auto&& v : streamingData["adaptiveFormats"].toArray())
                adaptiveFormats.append(StreamingFormat(v.toObject()));
            for (auto&& v : streamingData["formats"].toArray())
                formats.append(StreamingFormat(v.toObject()));
        }
    };
}

#endif // STREAMINGDATA_H
