#ifndef BROWSEHISTORY_H
#define BROWSEHISTORY_H
#include "innertube/endpoints/base/basebrowseendpoint.h"
#include "innertube/responses/browse/historyresponse.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Watch history.
     * @details Used on the history page - youtube.com/feed/history.
     */
    class BrowseHistory : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
    public:
        QString continuationToken;
        HistoryResponse response;
    protected:
        /**
         * @param tokenIn  Continuation token.
         */
        BrowseHistory(const QString& query, InnertubeContext* context, InnertubeAuthStore* authStore, const QString& tokenIn = "");
    };
}

#endif // BROWSEHISTORY_H
