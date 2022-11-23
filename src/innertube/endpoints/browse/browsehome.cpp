#include "browsehome.h"
#include "innertube/innertubeexception.h"
#include <QJsonArray>
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    BrowseHome::BrowseHome(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore, const QString& tokenIn)
        : BaseBrowseEndpoint("FEwhat_to_watch", context, easy, authStore, tokenIn)
    {
        QJsonArray gridContents;
        if (tokenIn.isEmpty())
        {
            QJsonObject tabRenderer = getTabRenderer("BrowseHome");
            gridContents = tabRenderer["richGridRenderer"].toObject()["contents"].toArray();
            if (gridContents.isEmpty())
                throw InnertubeException("[BrowseHome] richGridRenderer has no contents");
        }
        else
        {
            QJsonArray onResponseReceivedActions = QJsonDocument::fromJson(data).object()["onResponseReceivedActions"].toArray();
            if (onResponseReceivedActions.isEmpty())
                throw InnertubeException("[BrowseHome] Continuation has no actions", InnertubeException::Minor); // this can just happen sometimes

            QJsonObject appendItemsAction = onResponseReceivedActions[0].toObject()["appendContinuationItemsAction"].toObject();
            if (appendItemsAction.isEmpty())
                throw InnertubeException("[BrowseHome] Continuation has no appendContinuationItemsAction"); // now this shouldn't just happen

            gridContents = appendItemsAction["continuationItems"].toArray();
        }

        for (const QJsonValue& v : qAsConst(gridContents))
        {
            const QJsonObject o = v.toObject();
            if (o.contains("richItemRenderer"))
            {
                const QJsonObject videoRenderer = v["richItemRenderer"]["content"]["videoRenderer"].toObject();
                if (videoRenderer.isEmpty()) continue;
                response.videos.append(InnertubeObjects::Video(videoRenderer, false));
            }
            else if (o.contains("continuationItemRenderer"))
            {
                continuationToken = v["continuationItemRenderer"]["continuationEndpoint"]["continuationCommand"]["token"].toString();
            }
        }
    }
}
