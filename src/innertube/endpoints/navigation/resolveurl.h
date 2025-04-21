#pragma once
#include "innertube/endpoints/base/baseendpoint.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Attempt to resolve a suitable endpoint from a youtube.com URL.
     */

    struct ResolveUrl : BaseEndpoint<"navigation/resolve_url">
    {
        QJsonValue endpoint;

        explicit ResolveUrl(const QJsonValue& data);
        static QJsonObject createBody(const InnertubeContext* context, const QString& url);
    };
}
