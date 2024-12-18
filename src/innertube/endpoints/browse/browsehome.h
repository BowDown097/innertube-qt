#pragma once
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
        BrowseHome(const InnertubeContext* context, const InnertubeAuthStore* authStore, const QString& tokenIn = "");

        explicit BrowseHome(const QJsonValue& data);
    };
}
