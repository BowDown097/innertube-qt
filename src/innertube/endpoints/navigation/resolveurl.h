#pragma once
#include "innertube/endpoints/base/baseendpoint.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Attempt to resolve a suitable endpoint from a youtube.com URL.
     */

    class ResolveUrl : public BaseEndpoint<"navigation/resolve_url">
    {
        friend class ::InnerTube;
    public:
        QJsonValue endpoint;
    protected:
        /**
         * @param url  URL to resolve.
         */
        ResolveUrl(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& url);
    };
}
