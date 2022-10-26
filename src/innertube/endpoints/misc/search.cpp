#include "search.h"
#include "innertube/innertubeexception.h"
#include <QJsonArray>
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    Search::Search(const QString& query, InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore, const QString& tokenIn)
    {
        QByteArray data;
        QJsonObject body = { { "context", context->toJson() } };
        if (tokenIn.isEmpty())
            body.insert("query", query);
        else
            body.insert("continuation", tokenIn);
        get("search", context, authStore, easy, body, data);

        QJsonObject dataObj = QJsonDocument::fromJson(data).object();
        response.estimatedResults = dataObj["estimatedResults"].toString().toLong();

        QJsonArray sectionListRenderer;
        if (tokenIn.isEmpty())
        {
            QJsonObject contents = dataObj["contents"].toObject();
            if (contents.isEmpty())
                throw InnertubeException("[Search] contents not found");

            QJsonObject resultsRenderer = contents["twoColumnSearchResultsRenderer"].toObject();
            if (resultsRenderer.isEmpty())
                throw InnertubeException("[Search] twoColumnSearchResultsRenderer not found");

            sectionListRenderer = resultsRenderer["primaryContents"].toObject()["sectionListRenderer"].toObject()["contents"].toArray();
            if (sectionListRenderer.isEmpty())
                throw InnertubeException("[Search] sectionListRenderer not found or is empty");
        }
        else
        {
            QJsonArray onResponseReceivedCommands = dataObj["onResponseReceivedCommands"].toArray();
            if (onResponseReceivedCommands.isEmpty())
                throw InnertubeException("[Search] Continuation has no commands", InnertubeException::Minor); // this can just happen sometimes

            QJsonObject appendItemsAction = onResponseReceivedCommands[0].toObject()["appendContinuationItemsAction"].toObject();
            if (appendItemsAction.isEmpty())
                throw InnertubeException("[Search] Continuation has no appendContinuationItemsAction"); // now this shouldn't just happen

            sectionListRenderer = appendItemsAction["continuationItems"].toArray();
        }

        for (auto&& v : sectionListRenderer)
        {
            QJsonObject o = v.toObject();
            if (o.contains("itemSectionRenderer"))
            {
                QJsonArray itemSectionRenderer = v.toObject()["itemSectionRenderer"].toObject()["contents"].toArray();
                if (itemSectionRenderer.isEmpty()) continue;

                for (auto&& v2 : itemSectionRenderer)
                {
                    QJsonObject o2 = v2.toObject();
                    if (o2.contains("videoRenderer"))
                        response.videos.append(InnertubeObjects::Video(o2["videoRenderer"].toObject(), false));
                    else if (o2.contains("channelRenderer"))
                        response.channels.append(InnertubeObjects::Channel(o2["channelRenderer"].toObject()));
                }
            }
            else if (o.contains("continuationItemRenderer"))
            {
                continuationToken = o["continuationItemRenderer"].toObject()["continuationEndpoint"].toObject()["continuationCommand"].toObject()["token"].toString();
            }
        }
    }
}
