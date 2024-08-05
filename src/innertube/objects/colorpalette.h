#pragma once
#include <QJsonValue>

namespace InnertubeObjects
{
    struct ColorPalette
    {
        uint32_t primaryTitleColor{};
        uint32_t secondaryTitleColor{};
        uint32_t section2Color{};
        uint32_t section3Color{};
        uint32_t section4Color{};

        ColorPalette() = default;
        explicit ColorPalette(const QJsonValue& value)
            : primaryTitleColor(value["primaryTitleColor"].toVariant().toUInt()),
              secondaryTitleColor(value["secondaryTitleColor"].toVariant().toUInt()),
              section2Color(value["section2Color"].toVariant().toUInt()),
              section3Color(value["section3Color"].toVariant().toUInt()),
              section4Color(value["section4Color"].toVariant().toUInt()) {}
    };
}
