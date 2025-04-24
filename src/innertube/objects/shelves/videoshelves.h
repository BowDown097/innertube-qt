#pragma once
#include "innertube/objects/items/horizontallist.h"
#include "innertube/objects/items/verticallist.h"
#include "innertube/objects/video/video.h"
#include "shelf.h"

namespace InnertubeObjects
{
    using HorizontalVideoShelf = Shelf<HorizontalList<Video>>;
    using StandardVideoShelf = Shelf<QList<Video>>;
    using VerticalVideoShelf = Shelf<VerticalList<Video>>;
}
