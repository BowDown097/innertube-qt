#pragma once
#include "innertube/endpoints/base/baseendpoint.h"

namespace InnertubeEndpoints
{
    template<CompTimeStr endpoint>
    class BaseLikeEndpoint : public BaseEndpoint<endpoint>
    {
    protected:
        /**
         * @param params  Supplied by many sources - see QtTube code for usage.
         */
        BaseLikeEndpoint(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& videoId, const QString& params)
        {
            const QJsonObject body {
                { "context", context->toJson() },
                { "params", params },
                { "target", QJsonObject { { "videoId", videoId } } }
            };

            BaseEndpoint<endpoint>::get(context, authStore, body);
        }
    };
}
