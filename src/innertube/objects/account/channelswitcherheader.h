#pragma once
#include "innertube/objects/items/button.h"

namespace InnertubeObjects
{
    struct ChannelSwitcherHeader
    {
        Button button;
        InnertubeString title;

        ChannelSwitcherHeader() = default;
        explicit ChannelSwitcherHeader(const QJsonValue& channelSwitcherHeaderRenderer)
            : button(channelSwitcherHeaderRenderer["button"]["buttonRenderer"]),
              title(channelSwitcherHeaderRenderer["title"]) {}
    };
}