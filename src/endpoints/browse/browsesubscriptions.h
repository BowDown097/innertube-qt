#ifndef BROWSESUBSCRIPTIONS_H
#define BROWSESUBSCRIPTIONS_H
#include <endpoints/base/basebrowseendpoint.h>
#include <objects/video/video.h>

namespace InnertubeEndpoints
{
    class BrowseSubscriptions : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
    public:
        QString continuationToken;
        QVector<InnertubeObjects::Video> videos;
    private:
        explicit BrowseSubscriptions(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore, const QString& tokenIn = "")
            : BaseBrowseEndpoint("FEsubscriptions", context, easy, authStore, tokenIn)
        {
            QJsonArray sectionListRenderer;
            if (tokenIn.isEmpty())
            {
                QJsonObject contents = QJsonDocument::fromJson(data).object()["contents"].toObject();
                if (contents.isEmpty())
                    throw InnertubeException("[BrowseSubscriptions] contents not found");

                QJsonObject resultsRenderer = contents["twoColumnBrowseResultsRenderer"].toObject();
                if (resultsRenderer.isEmpty())
                    throw InnertubeException("[BrowseSubscriptions] twoColumnBrowseResultsRenderer not found");

                QJsonArray tabs = resultsRenderer["tabs"].toArray();
                if (tabs.count() != 1)
                    throw InnertubeException(QStringLiteral("[BrowseSubscriptions] Expected 1 element in tabs, got %1").arg(tabs.count()));

                QJsonObject tabRenderer = tabs[0].toObject()["tabRenderer"].toObject()["content"].toObject();
                if (tabRenderer.isEmpty())
                    throw InnertubeException("[BrowseSubscriptions] tabRenderer not found");

                sectionListRenderer = tabRenderer["sectionListRenderer"].toObject()["contents"].toArray();
                if (sectionListRenderer.count() < 1)
                    throw InnertubeException("[BrowseSubscriptions] sectionListRenderer has no contents");
            }
            else
            {
                QJsonObject appendItemsAction = QJsonDocument::fromJson(data).object()["onResponseReceivedActions"].toArray()[0].toObject()["appendContinuationItemsAction"].toObject();
                if (appendItemsAction.isEmpty())
                    throw InnertubeException("[BrowseHome] Continuation has no appendContinuationItemsAction");

                sectionListRenderer = appendItemsAction["continuationItems"].toArray();
            }

            for (auto&& v : sectionListRenderer)
            {
                const QJsonObject& o = v.toObject();
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

                            videos.append(InnertubeObjects::Video(gridVideoRenderer, true));
                        }
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

#endif // BROWSESUBSCRIPTIONS_H
