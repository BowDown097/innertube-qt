#include "browsesubscriptions.h"
#include "innertube/innertubeexception.h"
#include <QJsonArray>
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    BrowseSubscriptions::BrowseSubscriptions(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore, const QString& tokenIn)
        : BaseBrowseEndpoint("FEsubscriptions", context, easy, authStore, tokenIn)
    {
        QJsonArray sectionListRenderer;
        if (tokenIn.isEmpty())
        {
            QJsonObject tabRenderer = getTabRenderer("BrowseSubscriptions");
            sectionListRenderer = tabRenderer["sectionListRenderer"].toObject()["contents"].toArray();
            if (sectionListRenderer.isEmpty())
                throw InnertubeException("[BrowseSubscriptions] sectionListRenderer has no contents");
        }
        else
        {
            QJsonArray onResponseReceivedActions = QJsonDocument::fromJson(data).object()["onResponseReceivedActions"].toArray();
            if (onResponseReceivedActions.isEmpty())
                throw InnertubeException("[BrowseSubscriptions] Continuation has no actions", InnertubeException::Minor); // this can just happen sometimes

            QJsonObject appendItemsAction = onResponseReceivedActions[0].toObject()["appendContinuationItemsAction"].toObject();
            if (appendItemsAction.isEmpty())
                throw InnertubeException("[BrowseSubscriptions] Continuation has no appendContinuationItemsAction"); // now this shouldn't just happen

            sectionListRenderer = appendItemsAction["continuationItems"].toArray();
        }

        for (auto&& v : sectionListRenderer)
        {
            QJsonObject o = v.toObject();
            if (o.contains("itemSectionRenderer"))
            {
                QJsonArray itemSectionContents = o["itemSectionRenderer"].toObject()["contents"].toArray();
                if (itemSectionContents.isEmpty())
                    throw InnertubeException("[BrowseSubscriptions] itemSectionRenderer not found or has no content");

                for (auto&& v2 : itemSectionContents)
                {
                    QJsonObject shelfRenderer = v2.toObject()["shelfRenderer"].toObject();
                    if (shelfRenderer.isEmpty()) continue;

                    QJsonArray gridContents = shelfRenderer["content"].toObject()["gridRenderer"].toObject()["items"].toArray();
                    for (auto&& v3 : gridContents)
                    {
                        QJsonObject gridVideoRenderer = v3.toObject()["gridVideoRenderer"].toObject();
                        if (gridVideoRenderer.isEmpty()) continue;
                        response.videos.append(InnertubeObjects::Video(gridVideoRenderer, true));
                    }
                }
            }
            else if (o.contains("continuationItemRenderer"))
            {
                continuationToken = o["continuationItemRenderer"].toObject()["continuationEndpoint"].toObject()["continuationCommand"].toObject()["token"].toString();
            }
        }
    }
}
