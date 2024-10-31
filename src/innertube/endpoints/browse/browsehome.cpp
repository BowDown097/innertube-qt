#include "browsehome.h"
#include "innertube/innertubeexception.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    BrowseHome::BrowseHome(const InnertubeContext* context, const InnertubeAuthStore* authStore, const QString& tokenIn)
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
            if (const QJsonValue richItem = v["richItemRenderer"]; richItem.isObject())
            {
                if (const QJsonValue video = richItem["content"]["videoRenderer"]; video.isObject())
                    response.videos.append(InnertubeObjects::Video(video));
            }
            else if (const QJsonValue shelf = v["shelfRenderer"]; shelf.isObject())
            {
                response.shelves.append(InnertubeObjects::InnertubeString(shelf["title"]));
                const QJsonArray shelfContents = shelf["content"]["horizontalListRenderer"]["items"].toArray();
                for (const QJsonValue& v2 : shelfContents)
                    if (const QJsonValue gridVideo = v2["gridVideoRenderer"]; gridVideo.isObject())
                        response.videos.append(InnertubeObjects::Video(gridVideo));
            }
            else if (const QJsonValue continuation = v["continuationItemRenderer"]; continuation.isObject())
            {
                continuationToken = continuation["continuationEndpoint"]["continuationCommand"]["token"].toString();
            }
        }
    }
}
