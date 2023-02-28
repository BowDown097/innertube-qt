#ifndef BROWSEHISTORY_H
#define BROWSEHISTORY_H
#include "innertube/endpoints/base/basebrowseendpoint.h"
#include "innertube/responses/browse/historyresponse.h"

namespace InnertubeEndpoints
{
    class BrowseHistory : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
    public:
        QString continuationToken;
        HistoryResponse response;
    private:
        BrowseHistory(const QString& query, InnertubeContext* context, InnertubeAuthStore* authStore, const QString& tokenIn = "");
    };
}

#endif // BROWSEHISTORY_H
