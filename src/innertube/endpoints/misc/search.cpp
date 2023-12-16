#include "search.h"
#include "innertube/innertubeexception.h"
#include <QJsonArray>
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    Search::Search(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& query,
                   const QString& tokenIn, const QString& params)
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

        QByteArray data = get(context, authStore, body);
        QJsonValue dataObj = QJsonDocument::fromJson(data).object();

        response.estimatedResults = dataObj["estimatedResults"].toString().toLong();

        QJsonArray sectionListRenderer;
        if (tokenIn.isEmpty())
        {
            QJsonValue contents = dataObj["contents"];
            if (!contents.isObject())
                throw InnertubeException("[Search] contents not found");

            QJsonValue resultsRenderer = contents["twoColumnSearchResultsRenderer"];
            if (!resultsRenderer.isObject())
                throw InnertubeException("[Search] twoColumnSearchResultsRenderer not found");

            sectionListRenderer = resultsRenderer["primaryContents"]["sectionListRenderer"]["contents"].toArray();
            if (sectionListRenderer.isEmpty())
                throw InnertubeException("[Search] sectionListRenderer not found or is empty");
        }
        else
        {
            const QJsonArray onResponseReceivedCommands = dataObj["onResponseReceivedCommands"].toArray();
            if (onResponseReceivedCommands.isEmpty())
                throw InnertubeException("[Search] Continuation has no commands", InnertubeException::Severity::Minor); // this can just happen sometimes

            QJsonValue appendItemsAction = onResponseReceivedCommands[0]["appendContinuationItemsAction"];
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
