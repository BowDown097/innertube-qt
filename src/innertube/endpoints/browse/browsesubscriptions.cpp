#include "browsesubscriptions.h"
#include "innertube/innertubeexception.h"
#include <QJsonArray>
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    BrowseSubscriptions::BrowseSubscriptions(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& tokenIn)
        : BaseBrowseEndpoint("FEsubscriptions", context, authStore, tokenIn)
    {
        QJsonArray richGridRenderer;
        if (tokenIn.isEmpty())
        {
            QJsonValue tabRenderer = getTabRenderer("BrowseSubscriptions");
            richGridRenderer = tabRenderer["richGridRenderer"]["contents"].toArray();
            if (richGridRenderer.isEmpty())
                throw InnertubeException("[BrowseSubscriptions] richGridRenderer has no contents");
        }
        else
        {
            const QJsonArray onResponseReceivedActions = QJsonDocument::fromJson(data)["onResponseReceivedActions"].toArray();
            if (onResponseReceivedActions.isEmpty())
                throw InnertubeException("[BrowseSubscriptions] Continuation has no actions", InnertubeException::Minor); // this can just happen sometimes

            QJsonValue appendItemsAction = onResponseReceivedActions[0]["appendContinuationItemsAction"];
            if (!appendItemsAction.isObject())
                throw InnertubeException("[BrowseSubscriptions] Continuation has no appendContinuationItemsAction"); // now this shouldn't just happen

            richGridRenderer = appendItemsAction["continuationItems"].toArray();
        }

        for (const QJsonValue& v : qAsConst(richGridRenderer))
        {
            if (v["richItemRenderer"].isObject())
            {
                QJsonValue richItemContents = v["richItemRenderer"]["content"];
                if (richItemContents["videoRenderer"].isObject())
                    response.videos.append(InnertubeObjects::Video(richItemContents["videoRenderer"], false));
            }
            else if (v["continuationItemRenderer"].isObject())
            {
                continuationToken = v["continuationItemRenderer"]["continuationEndpoint"]["continuationCommand"]["token"].toString();
            }
        }
    }
}
