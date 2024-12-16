#pragma once
#include "innertube/objects/viewmodels/lockupviewmodel.h"
#include "innertube/objects/video/video.h"

namespace InnertubeEndpoints
{
    using HomeResponseItem = std::variant<
        InnertubeObjects::InnertubeString, // shelf
        InnertubeObjects::LockupViewModel,
        InnertubeObjects::Video>;

    struct HomeResponse
    {
        QList<HomeResponseItem> contents;
    };
}
