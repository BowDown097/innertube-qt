#include "browsesubscriptions.h"
#include "innertube/innertubeexception.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    BrowseSubscriptions::BrowseSubscriptions(const InnertubeContext* context, const InnertubeAuthStore* authStore,
                                             const QString& tokenIn)
        : BrowseSubscriptions(fetch("FEsubscriptions", context, authStore, tokenIn)) {}

    BrowseSubscriptions::BrowseSubscriptions(const QJsonValue& data)
    {
        if (const QJsonValue onResponseReceivedValue = data["onResponseReceivedActions"]; onResponseReceivedValue.isArray())
        {
            const QJsonArray onResponseReceivedActions = onResponseReceivedValue.toArray();
            // this can just happen sometimes, so will only be minor
            if (onResponseReceivedActions.isEmpty())
                throw InnertubeException("[BrowseSubscriptions] Continuation has no actions", InnertubeException::Severity::Minor);

            const QJsonValue appendItemsAction = onResponseReceivedActions[0]["appendContinuationItemsAction"];
            // now this shouldn't just happen, so will not be minor
            if (!appendItemsAction.isObject())
                throw InnertubeException("[BrowseSubscriptions] Continuation has no appendContinuationItemsAction");

            const QJsonArray continuationItems = appendItemsAction["continuationItems"].toArray();
            for (const QJsonValue& v : continuationItems)
            {
                if (const QJsonValue itemSection = v["itemSectionRenderer"]; itemSection.isObject())
                    handleItemSection(itemSection);
                else if (const QJsonValue richItem = v["richItemRenderer"]; richItem.isObject())
                    handleRichItem(richItem);
                else if (const QJsonValue continuation = v["continuationItemRenderer"]; continuation.isObject())
                    continuationToken = continuation["continuationEndpoint"]["continuationCommand"]["token"].toString();
            }
        }
        else
        {
            const QJsonValue tabRenderer = getTabRenderer(data, "BrowseSubscriptions");
            if (const QJsonValue richGrid = tabRenderer["richGridRenderer"]; richGrid.isObject())
            {
                const QJsonArray richGridRenderer = richGrid["contents"].toArray();
                if (richGridRenderer.isEmpty())
                    throw InnertubeException("[BrowseSubscriptions] richGridRenderer has no contents");

                for (const QJsonValue& v : richGridRenderer)
                {
                    if (const QJsonValue richItem = v["richItemRenderer"]; richItem.isObject())
                        handleRichItem(richItem);
                    else if (const QJsonValue continuation = v["continuationItemRenderer"]; continuation.isObject())
                        continuationToken = continuation["continuationEndpoint"]["continuationCommand"]["token"].toString();
                }
            }
            else if (const QJsonValue sectionList = tabRenderer["sectionListRenderer"]; sectionList.isObject())
            {
                const QJsonArray sectionListRenderer = sectionList["contents"].toArray();
                if (sectionListRenderer.isEmpty())
                    throw InnertubeException("[BrowseSubscriptions] sectionListRenderer has no contents");

                for (const QJsonValue& v : sectionListRenderer)
                {
                    if (const QJsonValue itemSection = v["itemSectionRenderer"]; itemSection.isObject())
                        handleItemSection(itemSection);
                    else if (const QJsonValue continuation = v["continuationItemRenderer"]; continuation.isObject())
                        continuationToken = continuation["continuationEndpoint"]["continuationCommand"]["token"].toString();
                }
            }
            else
            {
                throw InnertubeException("[BrowseSubscriptions] Could not find richGridRenderer or sectionListRenderer");
            }
        }
    }

    void BrowseSubscriptions::handleItemSection(const QJsonValue& itemSection)
    {
        const QJsonArray itemSectionContents = itemSection["contents"].toArray();
        if (itemSectionContents.isEmpty())
            throw InnertubeException("[BrowseSubscriptions] itemSectionRenderer not found or has no content");

        for (const QJsonValue& v2 : itemSectionContents)
        {
            if (const QJsonValue shelf = v2["shelfRenderer"]; shelf.isObject())
            {
                const QJsonArray gridContents = shelf["content"]["gridRenderer"]["items"].toArray();
                for (const QJsonValue& v3 : gridContents)
                    if (const QJsonValue gridVideo = v3["gridVideoRenderer"]; gridVideo.isObject())
                        response.videos.append(InnertubeObjects::Video(gridVideo));
            }
        }
    }

    void BrowseSubscriptions::handleRichItem(const QJsonValue& richItem)
    {
        if (const QJsonValue video = richItem["content"]["videoRenderer"]; video.isObject())
            response.videos.append(InnertubeObjects::Video(video));
    }
}
