#include "search.h"
#include "innertube/innertubeexception.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    Search::Search(const InnertubeContext* context, const InnertubeAuthStore* authStore, const QString& query,
                   const QString& tokenIn, const QString& params)
        : Search(get(context, authStore, createBody(context, query, tokenIn, params))) {}

    Search::Search(const QJsonValue& data)
    {
        response.estimatedResults = data["estimatedResults"].toString().toLongLong();

        QJsonArray sectionListRenderer;
        if (const QJsonValue contents = data["contents"]; contents.isObject())
        {
            const QJsonValue resultsRenderer = contents["twoColumnSearchResultsRenderer"];
            if (!resultsRenderer.isObject())
                throw InnertubeException("[Search] twoColumnSearchResultsRenderer not found");

            sectionListRenderer = resultsRenderer["primaryContents"]["sectionListRenderer"]["contents"].toArray();
            if (sectionListRenderer.isEmpty())
                throw InnertubeException("[Search] sectionListRenderer not found or is empty");
        }
        else if (const QJsonValue onResponseReceivedValue = data["onResponseReceivedCommands"]; onResponseReceivedValue.isArray())
        {
            const QJsonArray onResponseReceivedCommands = onResponseReceivedValue.toArray();
            // this can just happen sometimes, so will only be minor
            if (onResponseReceivedCommands.isEmpty())
                throw InnertubeException("[Search] Continuation has no commands", InnertubeException::Severity::Minor);

            const QJsonValue appendItemsAction = onResponseReceivedCommands[0]["appendContinuationItemsAction"];
            // now this shouldn't just happen, so will not be minor
            if (!appendItemsAction.isObject())
                throw InnertubeException("[Search] Continuation has no appendContinuationItemsAction");

            sectionListRenderer = appendItemsAction["continuationItems"].toArray();
        }
        else
        {
            throw InnertubeException("[Search] Failed to find any content");
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
                        if (const QJsonValue verticalList = shelf["content"]["verticalListRenderer"]; verticalList.isObject())
                        {
                            response.contents.append(InnertubeObjects::VerticalVideoShelf(shelf,
                                InnertubeObjects::VerticalList<InnertubeObjects::Video>(verticalList, "videoRenderer")));
                        }
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

    QJsonObject Search::createBody(const InnertubeContext* context, const QString& query,
                                   const QString& tokenIn, const QString& params)
    {
        QJsonObject body = { { "context", context->toJson() } };
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

        return body;
    }
}
