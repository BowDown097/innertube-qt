#pragma once
#include "innertube/objects/shelves/videoshelves.h"
#include "innertube/objects/viewmodels/lockupviewmodel.h"

namespace InnertubeEndpoints
{
    using HomeResponseItem = std::variant<
        InnertubeObjects::HorizontalVideoShelf,
        InnertubeObjects::LockupViewModel,
        InnertubeObjects::RichVideoShelf,
        InnertubeObjects::Video>;

    struct HomeResponse
    {
        QList<HomeResponseItem> contents;
    };
}
