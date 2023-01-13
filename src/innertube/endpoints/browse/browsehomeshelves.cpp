#include "browsehomeshelves.h"
#include "innertube/innertubeexception.h"
#include <QJsonArray>
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    BrowseHomeShelves::BrowseHomeShelves(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore, const QString& tokenIn)
        : BaseBrowseEndpoint("FEwhat_to_watch", context, easy, authStore, tokenIn)
    {
        if (!(context->client.clientName == "ANDROID" && context->client.clientVersion == "15.14.33"))
            throw InnertubeException("[BrowseHomeShelves] Specific client is needed: name should be ANDROID, version should be 15.14.33");

        QJsonArray sectionListContents;
        if (tokenIn.isEmpty())
        {
            const QJsonObject tabRenderer = getTabRenderer("BrowseHome", "singleColumnBrowseResultsRenderer");
            sectionListContents = tabRenderer["sectionListRenderer"]["contents"].toArray();
            if (sectionListContents.isEmpty())
                throw InnertubeException("[BrowseHomeShelves] sectionListRenderer has no contents");
        }
        else
        {
            const QJsonArray onResponseReceivedActions = QJsonDocument::fromJson(data).object()["onResponseReceivedActions"].toArray();
            if (onResponseReceivedActions.isEmpty())
                throw InnertubeException("[BrowseHomeShelves] Continuation has no actions", InnertubeException::Minor); // this can just happen sometimes

            const QJsonObject appendItemsAction = onResponseReceivedActions[0]["appendContinuationItemsAction"].toObject();
            if (appendItemsAction.isEmpty())
                throw InnertubeException("[BrowseHomeShelves] Continuation has no appendContinuationItemsAction"); // now this shouldn't just happen

            sectionListContents = appendItemsAction["continuationItems"].toArray();
        }

        for (const QJsonValue& v : qAsConst(sectionListContents))
        {
            const QJsonObject o = v.toObject();
            if (o.contains("shelfRenderer"))
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
