#ifndef SEARCH_H
#define SEARCH_H
#include <endpoints/base/baseendpoint.h>
#include <objects/channel/channel.h>
#include <objects/video/video.h>

namespace InnertubeEndpoints
{
    class Search : BaseEndpoint
    {
        friend class ::InnerTube;
    public:
        QVector<InnertubeObjects::Channel> channels;
        QString continuationToken;
        long estimatedResults;
        QVector<InnertubeObjects::Video> videos;
    private:
        explicit Search(const QString& query, InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore, const QString& tokenIn = "")
        {
            easy->set(CURLOPT_URL, "https://www.youtube.com/youtubei/v1/search?key=AIzaSyAO_FJ2SlqU8Q4STEHLGCilw_Y9_11qcW8&prettyPrint=false");
            setNeededHeaders(easy, context, authStore);

            QJsonObject body = { { "context", context->toJson() } };
            if (tokenIn.isEmpty())
                body.insert("query", query);
            else
                body.insert("continuation", tokenIn);

            QByteArray data;
            getData(easy, body, data);

            QJsonObject dataObj = QJsonDocument::fromJson(data).object();
            estimatedResults = dataObj["estimatedResults"].toString().toLong();

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
                QJsonObject appendItemsAction = dataObj["onResponseReceivedCommands"].toArray()[0].toObject()["appendContinuationItemsAction"].toObject();
                if (appendItemsAction.isEmpty())
                    throw InnertubeException("[Search] Continuation has no appendContinuationItemsAction");

                sectionListRenderer = appendItemsAction["continuationItems"].toArray();
            }

            for (auto&& v : sectionListRenderer)
            {
                const QJsonObject& o = v.toObject();
                if (o.contains("itemSectionRenderer"))
                {
                    QJsonArray itemSectionRenderer = v.toObject()["itemSectionRenderer"].toObject()["contents"].toArray();
                    if (itemSectionRenderer.isEmpty()) continue;

                    for (auto&& v2 : itemSectionRenderer)
                    {
                        const QJsonObject& o2 = v2.toObject();
                        if (o2.contains("videoRenderer"))
                            videos.append(InnertubeObjects::Video(o2["videoRenderer"].toObject(), false));
                        else if (o2.contains("channelRenderer"))
                            channels.append(InnertubeObjects::Channel(o2["channelRenderer"].toObject()));
                    }
                }
                else if (o.contains("continuationItemRenderer"))
                {
                    continuationToken = o["continuationItemRenderer"].toObject()["continuationEndpoint"].toObject()["continuationCommand"].toObject()["token"].toString();
                }
            }
        }
    };
}

#endif // SEARCH_H
