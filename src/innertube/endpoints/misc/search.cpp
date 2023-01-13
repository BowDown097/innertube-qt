#include "search.h"
#include "innertube/innertubeexception.h"
#include <QJsonArray>
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    Search::Search(const QString& query, InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore, const QString& tokenIn, const QString& params)
    {
        QJsonObject body = { { "context", context->toJson() } };
        if (tokenIn.isEmpty())
        {
            body.insert("query", query);
            if (!params.isEmpty()) body.insert("params", params);
        }
        else
        {
            body.insert("continuation", tokenIn);
        }

        QByteArray data;
        get("search", context, authStore, easy, body, data);

        const QJsonObject dataObj = QJsonDocument::fromJson(data).object();
        response.estimatedResults = dataObj["estimatedResults"].toString().toLong();

        QJsonArray sectionListRenderer;
        if (tokenIn.isEmpty())
        {
            const QJsonObject contents = dataObj["contents"].toObject();
            if (contents.isEmpty())
                throw InnertubeException("[Search] contents not found");

            const QJsonObject resultsRenderer = contents["twoColumnSearchResultsRenderer"].toObject();
            if (resultsRenderer.isEmpty())
                throw InnertubeException("[Search] twoColumnSearchResultsRenderer not found");

            sectionListRenderer = resultsRenderer["primaryContents"]["sectionListRenderer"]["contents"].toArray();
            if (sectionListRenderer.isEmpty())
                throw InnertubeException("[Search] sectionListRenderer not found or is empty");
        }
        else
        {
            const QJsonArray onResponseReceivedCommands = dataObj["onResponseReceivedCommands"].toArray();
            if (onResponseReceivedCommands.isEmpty())
                throw InnertubeException("[Search] Continuation has no commands", InnertubeException::Minor); // this can just happen sometimes

            const QJsonObject appendItemsAction = onResponseReceivedCommands[0]["appendContinuationItemsAction"].toObject();
            if (appendItemsAction.isEmpty())
                throw InnertubeException("[Search] Continuation has no appendContinuationItemsAction"); // now this shouldn't just happen

            sectionListRenderer = appendItemsAction["continuationItems"].toArray();
        }

        for (const QJsonValue& v : qAsConst(sectionListRenderer))
        {
            const QJsonObject o = v.toObject();
            if (o.contains("itemSectionRenderer"))
            {
                const QJsonArray itemSectionRenderer = v["itemSectionRenderer"]["contents"].toArray();
                for (const QJsonValue& v2 : itemSectionRenderer)
                {
                    const QJsonObject o2 = v2.toObject();
                    if (o2.contains("videoRenderer"))
                        response.videos.append(InnertubeObjects::Video(o2["videoRenderer"], false));
                    else if (o2.contains("channelRenderer"))
                        response.channels.append(InnertubeObjects::SearchChannel(o2["channelRenderer"]));
                }
            }
            else if (o.contains("continuationItemRenderer"))
            {
                continuationToken = v["continuationItemRenderer"]["continuationEndpoint"]["continuationCommand"]["token"].toString();
            }
        }
    }
}
