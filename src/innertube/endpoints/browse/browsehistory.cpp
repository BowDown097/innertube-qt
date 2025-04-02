#include "browsehistory.h"
#include "innertube/innertubeexception.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    BrowseHistory::BrowseHistory(const InnertubeContext* context, const InnertubeAuthStore* authStore,
                                 const QString& query, const QString& tokenIn)
        : BrowseHistory(fetch("FEhistory", context, authStore, tokenIn, query)) {}

    BrowseHistory::BrowseHistory(const QJsonValue& data)
    {
        QJsonArray sectionListRenderer;
        if (const QJsonValue contents = data["contents"]; contents.isObject())
        {
            const QJsonValue tabRenderer = getTabRenderer(contents, "BrowseHistory");
            sectionListRenderer = tabRenderer["sectionListRenderer"]["contents"].toArray();
            if (sectionListRenderer.isEmpty())
                throw InnertubeException("[BrowseHistory] sectionListRenderer has no contents");
        }
        else if (const QJsonValue onResponseReceivedValue = data["onResponseReceivedActions"]; onResponseReceivedValue.isArray())
        {
            const QJsonArray onResponseReceivedActions = onResponseReceivedValue.toArray();
            // this can just happen sometimes, so will only be minor
            if (onResponseReceivedActions.isEmpty())
                throw InnertubeException("[BrowseHistory] Continuation has no actions", InnertubeException::Severity::Minor);

            const QJsonValue appendItemsAction = onResponseReceivedActions[0]["appendContinuationItemsAction"];
            // now this shouldn't just happen, so will not be minor
            if (!appendItemsAction.isObject())
                throw InnertubeException("[BrowseHistory] Continuation has no appendContinuationItemsAction");

            sectionListRenderer = appendItemsAction["continuationItems"].toArray();
        }
        else
        {
            throw InnertubeException("[BrowseHistory] Failed to find any content");
        }

        for (const QJsonValue& v : std::as_const(sectionListRenderer))
        {
            if (const QJsonValue itemSection = v["itemSectionRenderer"]; itemSection.isObject())
            {
                const QJsonArray itemSectionContents = itemSection["contents"].toArray();
                if (itemSectionContents.isEmpty())
                    throw InnertubeException("[BrowseHistory] itemSectionRenderer not found or has no content");

                for (const QJsonValue& v2 : itemSectionContents)
                    if (const QJsonValue video = v2["videoRenderer"]; video.isObject())
                        response.videos.append(InnertubeObjects::Video(video));
            }
            else if (const QJsonValue continuation = v["continuationItemRenderer"]; continuation.isObject())
            {
                continuationToken = continuation["continuationEndpoint"]["continuationCommand"]["token"].toString();
            }
        }
    }
}
