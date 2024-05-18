#pragma once
#include "streamingformat.h"

namespace InnertubeObjects
{
    struct StreamingData
    {
        QList<StreamingFormat> adaptiveFormats;
        QString dashManifestUrl;
        QString expiresInSeconds;
        QList<StreamingFormat> formats;
        QString hlsManifestUrl;

        StreamingData() = default;
        explicit StreamingData(const QJsonValue& streamingData);
    };
}
