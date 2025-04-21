#pragma once
#include "innertube/endpoints/base/basebrowseendpoint.h"
#include "innertube/responses/browse/historyresponse.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Watch history.
     * @details Used on the history page - youtube.com/feed/history.
     */
    struct BrowseHistory : BaseBrowseEndpoint
    {
        QString continuationToken;
        HistoryResponse response;

        explicit BrowseHistory(const QJsonValue& data);
        static QJsonObject createBody(
            const InnertubeContext* context, const QString& query, const QString& continuationToken = "");
    };
}
