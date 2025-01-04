#pragma once
#include "innertube/objects/ad/adslot.h"
#include "innertube/objects/shelves/videoshelves.h"
#include "innertube/objects/viewmodels/lockupviewmodel.h"

namespace InnertubeEndpoints
{
    using HomeResponseItem = std::variant<
        InnertubeObjects::AdSlot,
        InnertubeObjects::HorizontalVideoShelf,
        InnertubeObjects::LockupViewModel,
        InnertubeObjects::RichVideoShelf,
        InnertubeObjects::Video>;

    struct HomeResponse
    {
        QList<HomeResponseItem> contents;
    };
}
