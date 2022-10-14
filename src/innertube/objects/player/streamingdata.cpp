#include "streamingdata.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    StreamingData::StreamingData(const QJsonObject& streamingData) : dashManifestUrl(streamingData["dashManifestUrl"].toString()),
        expiresInSeconds(streamingData["expiresInSeconds"].toString()), hlsManifestUrl(streamingData["hlsManifestUrl"].toString())
    {
        for (auto&& v : streamingData["adaptiveFormats"].toArray())
            adaptiveFormats.append(StreamingFormat(v.toObject()));
        for (auto&& v : streamingData["formats"].toArray())
            formats.append(StreamingFormat(v.toObject()));
    }
}
