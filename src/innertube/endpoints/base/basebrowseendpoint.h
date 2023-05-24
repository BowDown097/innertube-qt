#ifndef BASEBROWSEENDPOINT_H
#define BASEBROWSEENDPOINT_H
#include "baseendpoint.h"

namespace InnertubeEndpoints
{
    class BaseBrowseEndpoint : public BaseEndpoint
    {
    protected:
        QByteArray data;
        BaseBrowseEndpoint(const QString& browseId, InnertubeContext* context, InnertubeAuthStore* authStore,
                           const QString& continuationToken = "", const QString& query = "");
        QJsonValue getTabRenderer(const QString& name) const;
    };
}

#endif // BASEBROWSEENDPOINT_H
