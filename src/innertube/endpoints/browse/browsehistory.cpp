#include "browsehistory.h"
#include "innertube/innertubeexception.h"
#include <QJsonArray>
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    BrowseHistory::BrowseHistory(const QString& query, InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore, const QString& tokenIn)
        : BaseBrowseEndpoint("FEhistory", context, easy, authStore, tokenIn, query)
    {
        QJsonArray sectionListRenderer;
        if (tokenIn.isEmpty())
        {
            QJsonObject tabRenderer = getTabRenderer("BrowseHistory");
            sectionListRenderer = tabRenderer["sectionListRenderer"].toObject()["contents"].toArray();
            if (sectionListRenderer.isEmpty())
                throw InnertubeException("[BrowseHistory] sectionListRenderer has no contents");
        }
        else
        {
            QJsonArray onResponseReceivedActions = QJsonDocument::fromJson(data).object()["onResponseReceivedActions"].toArray();
            if (onResponseReceivedActions.isEmpty())
                throw InnertubeException("[BrowseHistory] Continuation has no actions", InnertubeException::Minor); // this can just happen sometimes

            QJsonObject appendItemsAction = onResponseReceivedActions[0].toObject()["appendContinuationItemsAction"].toObject();
            if (appendItemsAction.isEmpty())
                throw InnertubeException("[BrowseHistory] Continuation has no appendContinuationItemsAction"); // now this shouldn't just happen

            sectionListRenderer = appendItemsAction["continuationItems"].toArray();
        }

        for (const QJsonValue& v : qAsConst(sectionListRenderer))
        {
            const QJsonObject o = v.toObject();
            if (o.contains("itemSectionRenderer"))
            {
                const QJsonArray itemSectionContents = v["itemSectionRenderer"]["contents"].toArray();
                if (itemSectionContents.isEmpty())
                    throw InnertubeException("[BrowseHistory] itemSectionRenderer not found or has no content");

                for (const QJsonValue& v2 : itemSectionContents)
                {
                    const QJsonObject videoRenderer = v2["videoRenderer"].toObject();
                    if (videoRenderer.isEmpty()) continue;
                    response.videos.append(InnertubeObjects::Video(videoRenderer, false));
                }
            }
            else if (o.contains("continuationItemRenderer"))
            {
                continuationToken = v["continuationItemRenderer"]["continuationEndpoint"]["continuationCommand"]["token"].toString();
            }
        }
    }
}
