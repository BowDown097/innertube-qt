#pragma once
#include "innertube/objects/colorpalette.h"
#include "responsiveimage.h"

namespace InnertubeObjects
{
    struct ImageWithColorPalette : ResponsiveImage
    {
        ColorPalette darkColorPalette;
        ColorPalette lightColorPalette;

        ImageWithColorPalette() = default;
        explicit ImageWithColorPalette(const QJsonValue& data)
            : ResponsiveImage(data["thumbnails"]),
              darkColorPalette(data["darkColorPalette"]),
              lightColorPalette(data["lightColorPalette"]) {}
    };
}
