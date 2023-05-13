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
            const QJsonObject tabRenderer = getTabRenderer("BrowseSubscriptions");
            richGridRenderer = tabRenderer["richGridRenderer"]["contents"].toArray();
            if (richGridRenderer.isEmpty())
                throw InnertubeException("[BrowseSubscriptions] richGridRenderer has no contents");
        }
        else
        {
            const QJsonArray onResponseReceivedActions = QJsonDocument::fromJson(data).object()["onResponseReceivedActions"].toArray();
            if (onResponseReceivedActions.isEmpty())
                throw InnertubeException("[BrowseSubscriptions] Continuation has no actions", InnertubeException::Minor); // this can just happen sometimes

            const QJsonObject appendItemsAction = onResponseReceivedActions[0]["appendContinuationItemsAction"].toObject();
            if (appendItemsAction.isEmpty())
                throw InnertubeException("[BrowseSubscriptions] Continuation has no appendContinuationItemsAction"); // now this shouldn't just happen

            richGridRenderer = appendItemsAction["continuationItems"].toArray();
        }

        for (const QJsonValue& v : qAsConst(richGridRenderer))
        {
            const QJsonObject o = v.toObject();
            if (o.contains("richItemRenderer"))
            {
                const QJsonObject richItemContents = v["richItemRenderer"]["content"].toObject();
                if (richItemContents.contains("videoRenderer"))
                    response.videos.append(InnertubeObjects::Video(richItemContents["videoRenderer"], false));
            }
            else if (o.contains("continuationItemRenderer"))
            {
                continuationToken = v["continuationItemRenderer"]["continuationEndpoint"]["continuationCommand"]["token"].toString();
            }
        }
    }
}
