#include "browsehistory.h"
#include "innertube/innertubeexception.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    BrowseHistory::BrowseHistory(const InnertubeContext* context, const InnertubeAuthStore* authStore,
                                 const QString& query, const QString& tokenIn)
        : BaseBrowseEndpoint("FEhistory", context, authStore, tokenIn, query)
    {
        QJsonArray sectionListRenderer;
        if (tokenIn.isEmpty())
        {
            const QJsonValue tabRenderer = getTabRenderer("BrowseHistory");
            sectionListRenderer = tabRenderer["sectionListRenderer"]["contents"].toArray();
            if (sectionListRenderer.isEmpty())
                throw InnertubeException("[BrowseHistory] sectionListRenderer has no contents");
        }
        else
        {
            const QJsonArray onResponseReceivedActions = data["onResponseReceivedActions"].toArray();
            if (onResponseReceivedActions.isEmpty())
                throw InnertubeException("[BrowseHistory] Continuation has no actions", InnertubeException::Severity::Minor); // this can just happen sometimes

            const QJsonValue appendItemsAction = onResponseReceivedActions[0]["appendContinuationItemsAction"];
            if (!appendItemsAction.isObject())
                throw InnertubeException("[BrowseHistory] Continuation has no appendContinuationItemsAction"); // now this shouldn't just happen

            sectionListRenderer = appendItemsAction["continuationItems"].toArray();
        }

        for (const QJsonValue& v : std::as_const(sectionListRenderer))
        {
            if (v["itemSectionRenderer"].isObject())
            {
                const QJsonArray itemSectionContents = v["itemSectionRenderer"]["contents"].toArray();
                if (itemSectionContents.isEmpty())
                    throw InnertubeException("[BrowseHistory] itemSectionRenderer not found or has no content");

                for (const QJsonValue& v2 : itemSectionContents)
                    if (v2["videoRenderer"].isObject())
                        response.videos.append(InnertubeObjects::Video(v2["videoRenderer"]));
            }
            else if (v["continuationItemRenderer"].isObject())
            {
                continuationToken = v["continuationItemRenderer"]["continuationEndpoint"]["continuationCommand"]["token"].toString();
            }
        }
    }
}
