#ifndef BROWSEHOMESHELVES_H
#define BROWSEHOMESHELVES_H
#include "innertube/endpoints/base/basebrowseendpoint.h"
#include "innertube/responses/browse/homeshelvesresponse.h"

namespace InnertubeEndpoints
{
    class BrowseHomeShelves : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
    public:
        QString continuationToken;
        HomeShelvesResponse response;
    private:
        BrowseHomeShelves(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore, const QString& tokenIn = "");
    };
}

#endif // BROWSEHOMESHELVES_H
