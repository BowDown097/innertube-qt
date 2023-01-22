#include "browsehome.h"
#include "innertube/innertubeexception.h"
#include <QJsonArray>
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    BrowseHome::BrowseHome(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore, const QString& tokenIn)
        : BaseBrowseEndpoint("FEwhat_to_watch", context, easy, authStore, tokenIn)
    {
        QJsonArray contents;
        if (tokenIn.isEmpty())
        {
            const QJsonObject baseContents = QJsonDocument::fromJson(data).object()["contents"].toObject();
            if (baseContents.isEmpty())
                throw InnertubeException("[BrowseHome] contents not found");

            const QString baseRenderer = baseContents.contains("twoColumnBrowseResultsRenderer")
                    ? "twoColumnBrowseResultsRenderer"
                    : "singleColumnBrowseResultsRenderer";

            const QJsonObject resultsRenderer = baseContents[baseRenderer].toObject();
            if (resultsRenderer.isEmpty())
                throw InnertubeException(QStringLiteral("[BrowseHome] %1 not found").arg(baseRenderer));

            const QJsonArray tabs = resultsRenderer["tabs"].toArray();
            if (tabs.isEmpty())
                throw InnertubeException("[BrowseHome] tabs not found or is empty");

            const QJsonObject tabRenderer = tabs[0]["tabRenderer"]["content"].toObject();
            if (tabRenderer.isEmpty())
                throw InnertubeException("[BrowseHome] tabRenderer not found");

            // if two column, assume grid; if not, assume shelves
            contents = baseRenderer == "twoColumnBrowseResultsRenderer"
                    ? tabRenderer["richGridRenderer"]["contents"].toArray()
                    : tabRenderer["sectionListRenderer"]["contents"].toArray();
        }
        else
        {
            const QJsonArray onResponseReceivedActions = QJsonDocument::fromJson(data).object()["onResponseReceivedActions"].toArray();
            if (onResponseReceivedActions.isEmpty())
                throw InnertubeException("[BrowseHome] Continuation has no actions", InnertubeException::Minor); // this can just happen sometimes

            const QJsonObject appendItemsAction = onResponseReceivedActions[0]["appendContinuationItemsAction"].toObject();
            if (appendItemsAction.isEmpty())
                throw InnertubeException("[BrowseHome] Continuation has no appendContinuationItemsAction"); // now this shouldn't just happen

            contents = appendItemsAction["continuationItems"].toArray();
        }

        for (const QJsonValue& v : qAsConst(contents))
        {
            const QJsonObject o = v.toObject();
            if (o.contains("richItemRenderer"))
            {
                const QJsonObject videoRenderer = v["richItemRenderer"]["content"]["videoRenderer"].toObject();
                if (videoRenderer.isEmpty()) continue;
                response.videos.append(InnertubeObjects::Video(videoRenderer, false));
            }
            else if (o.contains("shelfRenderer"))
            {
                const QJsonObject shelfRenderer = v["shelfRenderer"].toObject();
                InnertubeObjects::InnertubeString shelfTitle(shelfRenderer["title"]);
                response.shelves.append(shelfTitle);

                const QJsonArray shelfContents = shelfRenderer["content"]["horizontalListRenderer"]["items"].toArray();
                for (const QJsonValue& v2 : shelfContents)
                {
                    const QJsonObject gridVideoRenderer = v2["gridVideoRenderer"].toObject();
                    if (gridVideoRenderer.isEmpty()) continue;
                    response.videos.append(InnertubeObjects::Video(gridVideoRenderer, true, shelfTitle));
                }
            }
            else if (o.contains("continuationItemRenderer"))
            {
                continuationToken = v["continuationItemRenderer"]["continuationEndpoint"]["continuationCommand"]["token"].toString();
            }
        }
    }
}
