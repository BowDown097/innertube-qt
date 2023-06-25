#include "browsehome.h"
#include "innertube/innertubeexception.h"
#include <QJsonArray>
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    BrowseHome::BrowseHome(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& tokenIn)
        : BaseBrowseEndpoint("FEwhat_to_watch", context, authStore, tokenIn)
    {
        QJsonArray contents;
        if (tokenIn.isEmpty())
        {
            QJsonValue baseContents = QJsonDocument::fromJson(data)["contents"];
            if (!baseContents.isObject())
                throw InnertubeException("[BrowseHome] contents not found");

            const QString baseRenderer = !baseContents["twoColumnBrowseResultsRenderer"].isUndefined()
                    ? "twoColumnBrowseResultsRenderer"
                    : "singleColumnBrowseResultsRenderer";

            QJsonValue resultsRenderer = baseContents[baseRenderer];
            if (!resultsRenderer.isObject())
                throw InnertubeException(QStringLiteral("[BrowseHome] %1 not found").arg(baseRenderer));

            const QJsonArray tabs = resultsRenderer["tabs"].toArray();
            if (tabs.isEmpty())
                throw InnertubeException("[BrowseHome] tabs not found or is empty");

            QJsonValue tabRenderer = tabs[0]["tabRenderer"]["content"];
            if (!tabRenderer.isObject())
                throw InnertubeException("[BrowseHome] tabRenderer not found");

            // if two column, assume grid; if not, assume shelves
            contents = baseRenderer == "twoColumnBrowseResultsRenderer"
                    ? tabRenderer["richGridRenderer"]["contents"].toArray()
                    : tabRenderer["sectionListRenderer"]["contents"].toArray();
        }
        else
        {
            const QJsonArray onResponseReceivedActions = QJsonDocument::fromJson(data)["onResponseReceivedActions"].toArray();
            if (onResponseReceivedActions.isEmpty())
                throw InnertubeException("[BrowseHome] Continuation has no actions", InnertubeException::Severity::Minor); // this can just happen sometimes

            QJsonValue appendItemsAction = onResponseReceivedActions[0]["appendContinuationItemsAction"];
            if (!appendItemsAction.isObject())
                throw InnertubeException("[BrowseHome] Continuation has no appendContinuationItemsAction"); // now this shouldn't just happen

            contents = appendItemsAction["continuationItems"].toArray();
        }

        for (const QJsonValue& v : qAsConst(contents))
        {
            if (v["richItemRenderer"].isObject())
            {
                QJsonValue videoRenderer = v["richItemRenderer"]["content"]["videoRenderer"];
                if (!videoRenderer.isObject()) continue;
                response.videos.append(InnertubeObjects::Video(videoRenderer, false));
            }
            else if (v["shelfRenderer"].isObject())
            {
                InnertubeObjects::InnertubeString shelfTitle(v["shelfRenderer"]["title"]);
                response.shelves.append(shelfTitle);

                const QJsonArray shelfContents = v["shelfRenderer"]["content"]["horizontalListRenderer"]["items"].toArray();
                for (const QJsonValue& v2 : shelfContents)
                {
                    if (!v2["gridVideoRenderer"].isObject()) continue;
                    response.videos.append(InnertubeObjects::Video(v2["gridVideoRenderer"], true, shelfTitle));
                }
            }
            else if (v["continuationItemRenderer"].isObject())
            {
                continuationToken = v["continuationItemRenderer"]["continuationEndpoint"]["continuationCommand"]["token"].toString();
            }
        }
    }
}
