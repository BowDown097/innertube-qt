#ifndef BROWSEHISTORY_H
#define BROWSEHISTORY_H
#include <endpoints/base/basebrowseendpoint.h>

namespace InnertubeEndpoints
{
    class BrowseHistory : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
    public:
        QString continuationToken;
        QVector<InnertubeObjects::Video> videos;
    private:
        BrowseHistory(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore, const QString& tokenIn = "")
            : BaseBrowseEndpoint("FEhistory", context, easy, authStore, tokenIn)
        {
            QJsonArray sectionListRenderer;
            if (tokenIn.isEmpty())
            {
                QJsonObject tabRenderer = getTabRenderer("BrowseHistory");
                sectionListRenderer = tabRenderer["sectionListRenderer"].toObject()["contents"].toArray();
                if (sectionListRenderer.isEmpty())
                    throw InnertubeException("[BrowseHistory] sectionListRenderer has no contents");
            }
            else
            {
                QJsonArray onResponseReceivedActions = QJsonDocument::fromJson(data).object()["onResponseReceivedActions"].toArray();
                if (onResponseReceivedActions.isEmpty())
                    throw InnertubeException("[BrowseHistory] Continuation has no actions", InnertubeException::Minor); // this can just happen sometimes

                QJsonObject appendItemsAction = onResponseReceivedActions[0].toObject()["appendContinuationItemsAction"].toObject();
                if (appendItemsAction.isEmpty())
                    throw InnertubeException("[BrowseHistory] Continuation has no appendContinuationItemsAction"); // now this shouldn't just happen

                sectionListRenderer = appendItemsAction["continuationItems"].toArray();
            }

            for (auto&& v : sectionListRenderer)
            {
                const QJsonObject& o = v.toObject();
                if (o.contains("itemSectionRenderer"))
                {
                    QJsonArray itemSectionContents = o["itemSectionRenderer"].toObject()["contents"].toArray();
                    if (itemSectionContents.isEmpty())
                        throw InnertubeException("[BrowseHistory] itemSectionRenderer not found or has no content");

                    for (auto&& v2 : itemSectionContents)
                    {
                        QJsonObject videoRenderer = v2.toObject()["videoRenderer"].toObject();
                        if (videoRenderer.isEmpty()) continue;
                        videos.append(InnertubeObjects::Video(videoRenderer, false));
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

#endif // BROWSEHISTORY_H
