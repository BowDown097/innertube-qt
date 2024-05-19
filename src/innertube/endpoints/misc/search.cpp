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
        response.estimatedResults = data["estimatedResults"].toString().toLong();

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
            if (v["itemSectionRenderer"].isObject())
            {
                const QJsonArray itemSectionRenderer = v["itemSectionRenderer"]["contents"].toArray();
                for (const QJsonValue& v2 : itemSectionRenderer)
                {
                    if (v2["videoRenderer"].isObject())
                        response.videos.append(InnertubeObjects::Video(v2["videoRenderer"]));
                    else if (v2["channelRenderer"].isObject())
                        response.channels.append(InnertubeObjects::Channel(v2["channelRenderer"]));
                }
            }
            else if (v["continuationItemRenderer"].isObject())
            {
                continuationToken = v["continuationItemRenderer"]["continuationEndpoint"]["continuationCommand"]["token"].toString();
            }
        }
    }
}
