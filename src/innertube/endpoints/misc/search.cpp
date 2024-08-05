#include "search.h"
#include "innertube/innertubeexception.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    Search::Search(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& query,
                   const QString& tokenIn, const QString& params)
    {
        QJsonObject body = { EndpointMethods::contextPair(context) };
        if (tokenIn.isEmpty())
        {
            body.insert("query", query);
            if (!params.isEmpty())
                body.insert("params", params);
        }
        else
        {
            body.insert("continuation", tokenIn);
        }

        const QJsonValue data = get(context, authStore, body);
        response.estimatedResults = data["estimatedResults"].toString().toLongLong();

        QJsonArray sectionListRenderer;
        if (tokenIn.isEmpty())
        {
            if (!data["contents"].isObject())
                throw InnertubeException("[Search] contents not found");

            const QJsonValue resultsRenderer = data["contents"]["twoColumnSearchResultsRenderer"];
            if (!resultsRenderer.isObject())
                throw InnertubeException("[Search] twoColumnSearchResultsRenderer not found");

            sectionListRenderer = resultsRenderer["primaryContents"]["sectionListRenderer"]["contents"].toArray();
            if (sectionListRenderer.isEmpty())
                throw InnertubeException("[Search] sectionListRenderer not found or is empty");
        }
        else
        {
            const QJsonArray onResponseReceivedCommands = data["onResponseReceivedCommands"].toArray();
            if (onResponseReceivedCommands.isEmpty())
                throw InnertubeException("[Search] Continuation has no commands", InnertubeException::Severity::Minor); // this can just happen sometimes

            const QJsonValue appendItemsAction = onResponseReceivedCommands[0]["appendContinuationItemsAction"];
            if (!appendItemsAction.isObject())
                throw InnertubeException("[Search] Continuation has no appendContinuationItemsAction"); // now this shouldn't just happen

            sectionListRenderer = appendItemsAction["continuationItems"].toArray();
        }

        for (const QJsonValue& v : std::as_const(sectionListRenderer))
        {
            if (const QJsonValue itemSection = v["itemSectionRenderer"]; itemSection.isObject())
            {
                const QJsonArray itemSectionRenderer = itemSection["contents"].toArray();
                for (const QJsonValue& v2 : itemSectionRenderer)
                {
                    if (const QJsonValue channel = v2["channelRenderer"]; channel.isObject())
                    {
                        response.contents.append(InnertubeObjects::Channel(channel));
                    }
                    else if (const QJsonValue reelShelf = v2["reelShelfRenderer"]; reelShelf.isObject())
                    {
                        response.contents.append(InnertubeObjects::ReelShelf(reelShelf));
                    }
                    else if (const QJsonValue shelf = v2["shelfRenderer"]; shelf.isObject())
                    {
                        response.contents.append(InnertubeObjects::VerticalVideoShelf(shelf,
                            InnertubeObjects::VerticalList<InnertubeObjects::Video>(
                                shelf["content"]["verticalListRenderer"], "videoRenderer")));
                    }
                    else if (const QJsonValue video = v2["videoRenderer"]; video.isObject())
                    {
                        response.contents.append(InnertubeObjects::Video(video));
                    }
                }
            }
            else if (const QJsonValue continuation = v["continuationItemRenderer"]; continuation.isObject())
            {
                continuationToken = continuation["continuationEndpoint"]["continuationCommand"]["token"].toString();
            }
        }
    }
}
