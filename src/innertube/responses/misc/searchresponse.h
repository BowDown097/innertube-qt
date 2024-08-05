#pragma once
#include "innertube/objects/channel/channel.h"
#include "innertube/objects/items/verticallist.h"
#include "innertube/objects/shelves/reelshelf.h"
#include "innertube/objects/shelves/shelf.h"
#include "innertube/objects/video/video.h"

namespace InnertubeObjects
{
    using VerticalVideoShelf = InnertubeObjects::Shelf<InnertubeObjects::VerticalList<InnertubeObjects::Video>>;
}

namespace InnertubeEndpoints
{
    using SearchResponseContents = QList<std::variant<
        InnertubeObjects::Channel,
        InnertubeObjects::ReelShelf,
        InnertubeObjects::VerticalVideoShelf,
        InnertubeObjects::Video>>;

    struct SearchResponse
    {
        SearchResponseContents contents;
        qint64 estimatedResults;
    };
}
