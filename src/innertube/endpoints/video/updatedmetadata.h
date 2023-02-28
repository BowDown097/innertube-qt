#ifndef UPDATEDMETADATA_H
#define UPDATEDMETADATA_H
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/responses/video/updatedmetadataresponse.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    class UpdatedMetadata : public BaseEndpoint
    {
        friend class ::InnerTube;
    public:
        UpdatedMetadataResponse response;
    private:
        UpdatedMetadata(const QString& videoId, InnertubeContext* context, InnertubeAuthStore* authStore);
        QJsonValue findAction(const QJsonArray& actions, const QString& name);
    };
}

#endif // UPDATEDMETADATA_H
