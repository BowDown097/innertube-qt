#include "browsehome.h"
#include "innertube/innertubeexception.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    BrowseHome::BrowseHome(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& tokenIn)
        : BaseBrowseEndpoint("FEwhat_to_watch", context, authStore, tokenIn)
    {
        QJsonArray contents;
        if (tokenIn.isEmpty())
        {
            if (!data["contents"].isObject())
                throw InnertubeException("[BrowseHome] contents not found");

            const QLatin1String baseRenderer(!data["contents"]["twoColumnBrowseResultsRenderer"].isUndefined()
                ? "twoColumnBrowseResultsRenderer" : "singleColumnBrowseResultsRenderer");
            const QJsonValue resultsRenderer = data["contents"][baseRenderer];
            if (!resultsRenderer.isObject())
                throw InnertubeException(QStringLiteral("[BrowseHome] %1 not found").arg(baseRenderer));

            const QJsonArray tabs = resultsRenderer["tabs"].toArray();
            if (tabs.isEmpty())
                throw InnertubeException("[BrowseHome] tabs not found or is empty");

            const QJsonValue tabRenderer = tabs[0]["tabRenderer"]["content"];
            if (!tabRenderer.isObject())
                throw InnertubeException("[BrowseHome] tabRenderer not found");

            // if two column, assume grid; if not, assume shelves
            contents = baseRenderer == "twoColumnBrowseResultsRenderer"
                    ? tabRenderer["richGridRenderer"]["contents"].toArray()
                    : tabRenderer["sectionListRenderer"]["contents"].toArray();
        }
        else
        {
            const QJsonArray onResponseReceivedActions = data["onResponseReceivedActions"].toArray();
            if (onResponseReceivedActions.isEmpty())
                throw InnertubeException("[BrowseHome] Continuation has no actions", InnertubeException::Severity::Minor); // this can just happen sometimes

            const QJsonValue appendItemsAction = onResponseReceivedActions[0]["appendContinuationItemsAction"];
            if (!appendItemsAction.isObject())
                throw InnertubeException("[BrowseHome] Continuation has no appendContinuationItemsAction"); // now this shouldn't just happen

            contents = appendItemsAction["continuationItems"].toArray();
        }

        for (const QJsonValue& v : std::as_const(contents))
        {
            if (v["richItemRenderer"].isObject())
            {
                const QJsonValue videoRenderer = v["richItemRenderer"]["content"]["videoRenderer"];
                if (videoRenderer.isObject())
                    response.videos.append(InnertubeObjects::Video(videoRenderer));
            }
            else if (v["shelfRenderer"].isObject())
            {
                const InnertubeObjects::InnertubeString shelfTitle(v["shelfRenderer"]["title"]);
                response.shelves.append(shelfTitle);

                const QJsonArray shelfContents = v["shelfRenderer"]["content"]["horizontalListRenderer"]["items"].toArray();
                for (const QJsonValue& v2 : shelfContents)
                    if (v2["gridVideoRenderer"].isObject())
                        response.videos.append(InnertubeObjects::Video(v2["gridVideoRenderer"], shelfTitle));
            }
            else if (v["continuationItemRenderer"].isObject())
            {
                continuationToken = v["continuationItemRenderer"]["continuationEndpoint"]["continuationCommand"]["token"].toString();
            }
        }
    }
}
