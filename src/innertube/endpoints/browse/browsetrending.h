#ifndef BROWSETRENDING_H
#define BROWSETRENDING_H
#include "innertube/endpoints/base/basebrowseendpoint.h"
#include "innertube/responses/browse/trendingresponse.h"

namespace InnertubeEndpoints
{
    class BrowseTrending : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
    public:
        TrendingResponse response;
    private:
        BrowseTrending(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore);
    };
}

#endif // BROWSETRENDING_H
