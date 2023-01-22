#ifndef BASEBROWSEENDPOINT_H
#define BASEBROWSEENDPOINT_H
#include "baseendpoint.h"

namespace InnertubeEndpoints
{
    class BaseBrowseEndpoint : public BaseEndpoint
    {
    protected:
        QByteArray data;
        BaseBrowseEndpoint(const QString& browseId, InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore,
                           const QString& continuationToken = "", const QString& query = "");
        QJsonObject getTabRenderer(const QString& name) const;
    };
}

#endif // BASEBROWSEENDPOINT_H
