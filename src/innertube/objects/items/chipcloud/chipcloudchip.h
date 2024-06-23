#pragma once
#include <QJsonValue>

namespace InnertubeObjects
{
    struct ChipCloudChip
    {
        bool isSelected{};
        QJsonValue navigationEndpoint;
        QString styleType;
        QString text;

        ChipCloudChip() = default;
        explicit ChipCloudChip(const QJsonValue& chipCloudChipRenderer)
            : isSelected(chipCloudChipRenderer["isSelected"].toBool()),
              navigationEndpoint(chipCloudChipRenderer["navigationEndpoint"]),
              styleType(chipCloudChipRenderer["style"]["styleType"].toString()),
              text(chipCloudChipRenderer["text"]["simpleText"].toString()) {}
    };
}
