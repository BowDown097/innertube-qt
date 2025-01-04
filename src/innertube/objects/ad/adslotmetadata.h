#pragma once
#include <QJsonValue>

namespace InnertubeObjects
{
    struct AdSlotLoggingData
    {
        QString serializedSlotAdServingDataEntry;

        AdSlotLoggingData() = default;
        explicit AdSlotLoggingData(const QJsonValue& adSlotLoggingData)
            : serializedSlotAdServingDataEntry(adSlotLoggingData["serializedSlotAdServingDataEntry"].toString()) {}
    };

    struct AdSlotMetadata
    {
        AdSlotLoggingData adSlotLoggingData;
        QString slotId;
        int slotPhysicalPosition{};
        QString slotType;

        AdSlotMetadata() = default;
        explicit AdSlotMetadata(const QJsonValue& adSlotMetadata)
            : adSlotLoggingData(adSlotMetadata["adSlotLoggingData"]),
              slotId(adSlotMetadata["slotId"].toString()),
              slotPhysicalPosition(adSlotMetadata["slotPhysicalPosition"].toInt()),
              slotType(adSlotMetadata["slotType"].toString()) {}
    };
}
