#ifndef BROWSEHOME_H
#define BROWSEHOME_H
#include "innertube/endpoints/base/basebrowseendpoint.h"
#include "innertube/responses/browse/homeresponse.h"

namespace InnertubeEndpoints
{
    class BrowseHome : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
    public:
        QString continuationToken;
        HomeResponse response;
    private:
        BrowseHome(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore, const QString& tokenIn = "");
    };
}

#endif // BROWSEHOME_H
