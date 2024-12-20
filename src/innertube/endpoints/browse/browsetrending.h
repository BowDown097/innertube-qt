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
        BrowseTrending(const InnertubeContext* context, const InnertubeAuthStore* authStore);
        explicit BrowseTrending(const QJsonValue& data);
    };
}
