#pragma once
#include "innertube/endpoints/base/basebrowseendpoint.h"
#include "innertube/responses/browse/homeresponse.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Home page.
     */
    struct BrowseHome : BaseBrowseEndpoint
    {
        QString continuationToken;
        HomeResponse response;

        explicit BrowseHome(const QJsonValue& data);
        static QJsonObject createBody(const InnertubeContext* context, const QString& continuationToken = "");
    };
}
