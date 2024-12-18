#pragma once
#include "innertube/objects/channel/channel.h"
#include "innertube/objects/shelves/reelshelf.h"
#include "innertube/objects/shelves/videoshelves.h"

namespace InnertubeEndpoints
{
    using SearchResponseItem = std::variant<
        InnertubeObjects::Channel,
        InnertubeObjects::ReelShelf,
        InnertubeObjects::VerticalVideoShelf,
        InnertubeObjects::Video>;

    struct SearchResponse
    {
        QList<SearchResponseItem> contents;
        qint64 estimatedResults;
    };
}
