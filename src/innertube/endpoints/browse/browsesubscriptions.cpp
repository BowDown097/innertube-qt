#include "browsesubscriptions.h"
#include "innertube/innertubeexception.h"
#include <QJsonArray>
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    BrowseSubscriptions::BrowseSubscriptions(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& tokenIn)
        : BaseBrowseEndpoint("FEsubscriptions", context, authStore, tokenIn)
    {
        if (tokenIn.isEmpty())
        {
            const QJsonValue tabRenderer = getTabRenderer("BrowseSubscriptions");
            if (tabRenderer["richGridRenderer"].isObject())
            {
                const QJsonArray richGridRenderer = tabRenderer["richGridRenderer"]["contents"].toArray();
                if (richGridRenderer.isEmpty())
                    throw InnertubeException("[BrowseSubscriptions] richGridRenderer has no contents");

                for (const QJsonValue& v : richGridRenderer)
                {
                    if (v["richItemRenderer"].isObject())
                        handleRichItem(v);
                    else if (v["continuationItemRenderer"].isObject())
                        continuationToken = v["continuationItemRenderer"]["continuationEndpoint"]["continuationCommand"]["token"].toString();
                }
            }
            else if (tabRenderer["sectionListRenderer"].isObject())
            {
                const QJsonArray sectionListRenderer = tabRenderer["sectionListRenderer"]["contents"].toArray();
                if (sectionListRenderer.isEmpty())
                    throw InnertubeException("[BrowseSubscriptions] sectionListRenderer has no contents");

                for (const QJsonValue& v : sectionListRenderer)
                {
                    if (v["itemSectionRenderer"].isObject())
                        handleItemSection(v);
                    else if (v["continuationItemRenderer"].isObject())
                        continuationToken = v["continuationItemRenderer"]["continuationEndpoint"]["continuationCommand"]["token"].toString();
                }
            }
            else
            {
                throw InnertubeException("[BrowseSubscriptions] Could not find richGridRenderer or sectionListRenderer");
            }
        }
        else
        {
            const QJsonArray onResponseReceivedActions = QJsonDocument::fromJson(data)["onResponseReceivedActions"].toArray();
            if (onResponseReceivedActions.isEmpty())
                throw InnertubeException("[BrowseSubscriptions] Continuation has no actions", InnertubeException::Minor); // this can just happen sometimes

            const QJsonValue appendItemsAction = onResponseReceivedActions[0]["appendContinuationItemsAction"];
            if (!appendItemsAction.isObject())
                throw InnertubeException("[BrowseSubscriptions] Continuation has no appendContinuationItemsAction"); // now this shouldn't just happen

            const QJsonArray continuationItems = appendItemsAction["continuationItems"].toArray();
            for (const QJsonValue& v : continuationItems)
            {
                if (v["itemSectionRenderer"].isObject())
                    handleItemSection(v);
                else if (v["richItemRenderer"].isObject())
                    handleRichItem(v);
                else if (v["continuationItemRenderer"].isObject())
                    continuationToken = v["continuationItemRenderer"]["continuationEndpoint"]["continuationCommand"]["token"].toString();
            }
        }
    }

    void BrowseSubscriptions::handleItemSection(const QJsonValue& v)
    {
        const QJsonArray itemSectionContents = v["itemSectionRenderer"]["contents"].toArray();
        if (itemSectionContents.isEmpty())
            throw InnertubeException("[BrowseSubscriptions] itemSectionRenderer not found or has no content");

        for (const QJsonValue& v2 : itemSectionContents)
        {
            if (!v2["shelfRenderer"].isObject()) continue;

            const QJsonArray gridContents = v2["shelfRenderer"]["content"]["gridRenderer"]["items"].toArray();
            for (const QJsonValue& v3 : gridContents)
            {
                if (!v3["gridVideoRenderer"].isObject()) continue;
                response.videos.append(InnertubeObjects::Video(v3["gridVideoRenderer"], true));
            }
        }
    }

    void BrowseSubscriptions::handleRichItem(const QJsonValue& v)
    {
        const QJsonValue richItemContents = v["richItemRenderer"]["content"];
        if (richItemContents["videoRenderer"].isObject())
            response.videos.append(InnertubeObjects::Video(richItemContents["videoRenderer"], false));
    }
}
