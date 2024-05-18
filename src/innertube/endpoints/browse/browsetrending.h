#pragma once
#include "innertube/endpoints/base/basebrowseendpoint.h"
#include "innertube/responses/browse/trendingresponse.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Trending page.
     */
    class BrowseTrending : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
    public:
        TrendingResponse response;
    protected:
        BrowseTrending(InnertubeContext* context, InnertubeAuthStore* authStore);
    };
}
