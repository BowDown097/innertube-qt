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
    public:
        QString continuationToken;
        SubscriptionsResponse response;

        explicit BrowseSubscriptions(const QJsonValue& data);
        static QJsonObject createBody(const InnertubeContext* context, const QString& continuationToken = "");
    private:
        void handleItemSection(const QJsonValue& itemSection);
        void handleRichItem(const QJsonValue& richItem);
    };
}
