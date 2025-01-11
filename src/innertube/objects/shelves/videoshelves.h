#pragma once
#include "innertube/objects/items/horizontallist.h"
#include "innertube/objects/items/verticallist.h"
#include "innertube/objects/video/video.h"
#include "shelf.h"

namespace InnertubeObjects
{
    using HorizontalVideoShelf = InnertubeObjects::Shelf<InnertubeObjects::HorizontalList<InnertubeObjects::Video>>;
    using StandardVideoShelf = InnertubeObjects::Shelf<QList<InnertubeObjects::Video>>;
    using VerticalVideoShelf = InnertubeObjects::Shelf<InnertubeObjects::VerticalList<InnertubeObjects::Video>>;
}
