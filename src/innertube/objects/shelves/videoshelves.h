#pragma once
#include "innertube/objects/items/horizontallist.h"
#include "innertube/objects/items/verticallist.h"
#include "innertube/objects/video/video.h"
#include "innertube/objects/viewmodels/lockupviewmodel.h"
#include "innertube/objects/viewmodels/shortslockupviewmodel.h"
#include "richshelf.h"
#include "shelf.h"

namespace InnertubeObjects
{
    using HorizontalVideoShelf = InnertubeObjects::Shelf<InnertubeObjects::HorizontalList<InnertubeObjects::Video>>;
    using RichVideoShelf = InnertubeObjects::RichShelf<
        InnertubeObjects::LockupViewModel,
        InnertubeObjects::ShortsLockupViewModel,
        InnertubeObjects::Video>;
    using StandardVideoShelf = InnertubeObjects::Shelf<QList<InnertubeObjects::Video>>;
    using VerticalVideoShelf = InnertubeObjects::Shelf<InnertubeObjects::VerticalList<InnertubeObjects::Video>>;
}
