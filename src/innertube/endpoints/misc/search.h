#pragma once
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/responses/misc/searchresponse.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Search page.
     */
    class Search : public BaseEndpoint<"search">
    {
        friend class ::InnerTube;
    public:
        QString continuationToken;
        SearchResponse response;
    protected:
        /**
         * @param query  What to search for.
         * @param tokenIn  Continuation token.
         * @param params  Protobuf string for search filters - see [QtTube code](https://github.com/search?q=repo%3ABowDown097%2FQtTube+BrowseHelper%3A%3Asearch&type=code) for more details.
         */
        Search(const InnertubeContext* context, const InnertubeAuthStore* authStore, const QString& query,
               const QString& tokenIn = "", const QString& params = "");

        explicit Search(const QJsonValue& data);
    private:
        static QJsonObject createBody(const InnertubeContext* context, const QString& query,
                                      const QString& tokenIn, const QString& params);
    };
}
