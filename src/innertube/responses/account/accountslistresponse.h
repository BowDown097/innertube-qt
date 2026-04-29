#pragma once
#include "innertube/objects/account/channelswitcherpage.h"

namespace InnertubeEndpoints
{
    struct AccountsListResponse
    {
        InnertubeObjects::ChannelSwitcherPage page;
        QString selectText;
    };
}