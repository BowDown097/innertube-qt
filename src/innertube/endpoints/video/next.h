#pragma once
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/responses/video/nextresponse.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Most of the data, such as the title, description, and comments, for a video.
     */
    class Next : public BaseEndpoint<"next">
    {
        friend class ::InnerTube;
    public:
        NextResponse response;
    protected:
        /**
         * @param tokenIn  Continuation token for comments.
         */
        Next(const InnertubeContext* context, const InnertubeAuthStore* authStore,
             const QString& videoId, const QString& tokenIn = "");

        explicit Next(const QJsonValue& data);
    private:
        static QJsonObject createBody(const InnertubeContext* context, const QString& videoId, const QString& tokenIn);
    };
}
