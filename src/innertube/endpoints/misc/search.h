#ifndef SEARCH_H
#define SEARCH_H
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/responses/misc/searchresponse.h"

namespace InnertubeEndpoints
{
    class Search : public BaseEndpoint
    {
        friend class ::InnerTube;
    public:
        QString continuationToken;
        SearchResponse response;
    private:
        Search(const QString& query, InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore, const QString& tokenIn = "",
               const QString& params = "");
    };
}

#endif // SEARCH_H
