#ifndef BROWSESUBSCRIPTIONS_H
#define BROWSESUBSCRIPTIONS_H
#include "innertube/endpoints/base/basebrowseendpoint.h"
#include "innertube/responses/browse/subscriptionsresponse.h"

namespace InnertubeEndpoints
{
    class BrowseSubscriptions : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
    public:
        QString continuationToken;
        SubscriptionsResponse response;
    private:
        BrowseSubscriptions(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& tokenIn = "");
        void handleItemSection(const QJsonValue& v);
        void handleRichItem(const QJsonValue& v);
    };
}

#endif // BROWSESUBSCRIPTIONS_H
