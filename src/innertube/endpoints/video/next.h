#pragma once
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/responses/video/nextresponse.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Most of the data, such as the title, description, and comments, for a video.
     */
    struct Next : BaseEndpoint<"next">
    {
        NextResponse response;

        explicit Next(const QJsonValue& data);

        /**
         * @param continuationToken  Continuation token for comments.
         */
        static QJsonObject createBody(
            const InnertubeContext* context, const QString& videoId, const QString& continuationToken = "");
    };
}
