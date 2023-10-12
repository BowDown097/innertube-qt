#ifndef BROWSEHOME_H
#define BROWSEHOME_H
#include "innertube/endpoints/base/basebrowseendpoint.h"
#include "innertube/responses/browse/homeresponse.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Home page.
     */
    class BrowseHome : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
    public:
        QString continuationToken;
        HomeResponse response;
    protected:
        /**
         * @param tokenIn  Continuation token.
         */
        BrowseHome(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& tokenIn = "");
    };
}

#endif // BROWSEHOME_H
