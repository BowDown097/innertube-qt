#ifndef UPDATEDMETADATA_H
#define UPDATEDMETADATA_H
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/responses/video/updatedmetadataresponse.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    /**
     * @brief Info for the title, description, like count, and view count of a video.
     * Used for efficiently updating the video info during live viewing.
     */
    class UpdatedMetadata : public BaseEndpoint
    {
        friend class ::InnerTube;
    public:
        UpdatedMetadataResponse response;
    protected:
        UpdatedMetadata(const QString& videoId, InnertubeContext* context, InnertubeAuthStore* authStore);
    private:
        QJsonValue findAction(const QJsonArray& actions, const QString& name);
    };
}

#endif // UPDATEDMETADATA_H
