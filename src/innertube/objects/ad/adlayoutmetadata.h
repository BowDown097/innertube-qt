#pragma once
#include <QJsonValue>

namespace InnertubeObjects
{
    struct AdLayoutLoggingData
    {
        QString serializedAdServingDataEntry;

        AdLayoutLoggingData() = default;
        explicit AdLayoutLoggingData(const QJsonValue& adLayoutLoggingData)
            : serializedAdServingDataEntry(adLayoutLoggingData["serializedAdServingDataEntry"].toString()) {}
    };

    struct AdLayoutMetadata
    {
        AdLayoutLoggingData adLayoutLoggingData;
        QString layoutId;
        QString layoutType;

        AdLayoutMetadata() = default;
        explicit AdLayoutMetadata(const QJsonValue& adLayoutMetadata)
            : adLayoutLoggingData(adLayoutMetadata["adLayoutLoggingData"]),
              layoutId(adLayoutMetadata["layoutId"].toString()),
              layoutType(adLayoutMetadata["layoutType"].toString()) {}
    };
}
