#pragma once
#include "innertube/objects/items/horizontallist.h"
#include "innertube/objects/shelves/reelshelf.h"
#include "innertube/objects/shelves/shelf.h"
#include "innertube/objects/video/video.h"

namespace InnertubeObjects
{
    using HorizontalVideoShelf = InnertubeObjects::Shelf<InnertubeObjects::HorizontalList<InnertubeObjects::Video>>;
    using StandardVideoShelf = InnertubeObjects::Shelf<QList<InnertubeObjects::Video>>;
}

namespace InnertubeEndpoints
{
    using TrendingResponseContents = QList<std::variant<
        InnertubeObjects::HorizontalVideoShelf,
        InnertubeObjects::ReelShelf,
        InnertubeObjects::StandardVideoShelf>>;

    struct TrendingResponse
    {
        TrendingResponseContents contents;
    };
}
