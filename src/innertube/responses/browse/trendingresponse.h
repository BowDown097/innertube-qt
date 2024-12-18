#pragma once
#include "innertube/objects/shelves/reelshelf.h"
#include "innertube/objects/shelves/videoshelves.h"

namespace InnertubeEndpoints
{
    using TrendingResponseItem = std::variant<
        InnertubeObjects::HorizontalVideoShelf,
        InnertubeObjects::ReelShelf,
        InnertubeObjects::StandardVideoShelf>;

    struct TrendingResponse
    {
        QList<TrendingResponseItem> contents;
    };
}
