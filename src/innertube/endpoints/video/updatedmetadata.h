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
        friend class ::InnerTube;
    public:
        UpdatedMetadataResponse response;
    protected:
        UpdatedMetadata(const InnertubeContext* context, const InnertubeAuthStore* authStore, const QString& videoId);
    private:
        QJsonValue findAction(const QJsonArray& actions, const QString& name) const;
    };
}
