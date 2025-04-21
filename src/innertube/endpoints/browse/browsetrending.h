#pragma once
#include "innertube/endpoints/base/basebrowseendpoint.h"
#include "innertube/responses/browse/trendingresponse.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Trending page.
     */
    struct BrowseTrending : BaseBrowseEndpoint
    {
        TrendingResponse response;

        explicit BrowseTrending(const QJsonValue& data);
        static QJsonObject createBody(const InnertubeContext* context);
    };
}
