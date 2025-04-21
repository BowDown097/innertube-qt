#pragma once
#include "innertube/endpoints/base/baseendpoint.h"

namespace InnertubeEndpoints
{
    template<CompTimeStr endpoint>
    struct BaseLikeEndpoint : BaseEndpoint<endpoint>
    {
        /**
         * @param params  Supplied by many sources - see QtTube code for usage.
         */
        static QJsonObject createBody(const InnertubeContext* context, const QString& videoId, const QString& params)
        {
            return {
                { "context", context->toJson() },
                { "params", params },
                { "target", QJsonObject { { "videoId", videoId } } }
            };
        }
    };
}
