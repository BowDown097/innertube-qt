#ifndef BROWSESUBSCRIPTIONS_H
#define BROWSESUBSCRIPTIONS_H
#include "innertube/endpoints/base/basebrowseendpoint.h"
#include "innertube/responses/browse/subscriptionsresponse.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Subscribed channel activity.
     * @details Used on the subscriptions page - youtube.com/feed/subscriptions.
     */
    class BrowseSubscriptions : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
    public:
        QString continuationToken;
        SubscriptionsResponse response;
    protected:
        /**
         * @param tokenIn  Continuation token.
         */
        BrowseSubscriptions(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& tokenIn = "");
    private:
        void handleItemSection(const QJsonValue& v);
        void handleRichItem(const QJsonValue& v);
    };
}

#endif // BROWSESUBSCRIPTIONS_H
