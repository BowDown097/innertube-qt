#include "streamingdata.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    StreamingData::StreamingData(const QJsonValue& streamingData) : dashManifestUrl(streamingData["dashManifestUrl"].toString()),
        expiresInSeconds(streamingData["expiresInSeconds"].toString()), hlsManifestUrl(streamingData["hlsManifestUrl"].toString())
    {
        const QJsonArray adaptiveFormatsJson = streamingData["adaptiveFormats"].toArray();
        const QJsonArray formatsJson = streamingData["formats"].toArray();
        for (const QJsonValue& v : adaptiveFormatsJson)
            adaptiveFormats.append(StreamingFormat(v));
        for (const QJsonValue& v : formatsJson)
            formats.append(StreamingFormat(v));
    }
}
