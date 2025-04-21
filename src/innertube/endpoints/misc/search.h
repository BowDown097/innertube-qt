#pragma once
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/responses/misc/searchresponse.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Search page.
     */
    struct Search : BaseEndpoint<"search">
    {
        QString continuationToken;
        SearchResponse response;

        explicit Search(const QJsonValue& data);
        static QJsonObject createBody(
            const InnertubeContext* context, const QString& query,
            const QString& continuationToken = "", const QString& params = "");
    };
}
