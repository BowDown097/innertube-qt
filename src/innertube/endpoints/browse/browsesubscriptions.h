#pragma once
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
        BrowseSubscriptions(const InnertubeContext* context, const InnertubeAuthStore* authStore, const QString& tokenIn = "");

        explicit BrowseSubscriptions(const QJsonValue& data);
    private:
        void handleItemSection(const QJsonValue& itemSection);
        void handleRichItem(const QJsonValue& richItem);
    };
}
