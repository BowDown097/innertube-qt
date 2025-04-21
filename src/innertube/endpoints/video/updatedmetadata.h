#pragma once
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/responses/video/updatedmetadataresponse.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Info for the title, description, like count, and view count of a video.
     * Used for efficiently updating the video info during live viewing.
     */
    class UpdatedMetadata : public BaseEndpoint<"updated_metadata">
    {
    public:
        UpdatedMetadataResponse response;

        explicit UpdatedMetadata(const QJsonValue& data);
        static QJsonObject createBody(const InnertubeContext* context, const QString& videoId);
    private:
        static QJsonValue findAction(const QJsonArray& actions, const QString& name);
    };
}
