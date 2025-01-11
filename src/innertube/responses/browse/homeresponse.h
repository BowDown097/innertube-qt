#pragma once
#include "innertube/objects/ad/adslot.h"
#include "innertube/objects/backstage/post.h"
#include "innertube/objects/shelves/richshelf.h"
#include "innertube/objects/shelves/videoshelves.h"
#include "innertube/objects/viewmodels/lockupviewmodel.h"
#include "innertube/objects/viewmodels/minigamecardviewmodel.h"
#include "innertube/objects/viewmodels/shortslockupviewmodel.h"

namespace InnertubeObjects
{
    using HomeRichShelf = InnertubeObjects::RichShelf<
        InnertubeObjects::LockupViewModel,
        InnertubeObjects::MiniGameCardViewModel,
        InnertubeObjects::Post,
        InnertubeObjects::ShortsLockupViewModel,
        InnertubeObjects::Video>;
}

namespace InnertubeEndpoints
{
    using HomeResponseItem = std::variant<
        InnertubeObjects::AdSlot,
        InnertubeObjects::HomeRichShelf,
        InnertubeObjects::HorizontalVideoShelf,
        InnertubeObjects::LockupViewModel,
        InnertubeObjects::Video>;

    struct HomeResponse
    {
        QList<HomeResponseItem> contents;
    };
}
