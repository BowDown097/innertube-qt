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
                           const QString& continuationToken = "");
        QJsonObject getTabRenderer(const QString& name, const QString& baseRenderer = "twoColumnBrowseResultsRenderer");
    };
}

#endif // BASEBROWSEENDPOINT_H
