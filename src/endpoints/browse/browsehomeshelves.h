#ifndef BROWSEHOMESHELVES_H
#define BROWSEHOMESHELVES_H
#include <endpoints/base/basebrowseendpoint.h>

namespace InnertubeEndpoints
{
    class BrowseHomeShelves : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
    public:
        QString continuationToken;
        QVector<InnertubeObjects::InnertubeString> shelves;
        QVector<InnertubeObjects::Video> videos;
    private:
        BrowseHomeShelves(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore, const QString& tokenIn = "")
            : BaseBrowseEndpoint("FEwhat_to_watch", context, easy, authStore, tokenIn)
        {
            if (!(context->client.clientName == "ANDROID" && context->client.clientVersion == "15.14.33"))
                throw InnertubeException("[BrowseHomeShelves] Specific client is needed: name should be ANDROID, version should be 15.14.33");

            QJsonArray sectionListContents;
            if (tokenIn.isEmpty())
            {
                QJsonObject tabRenderer = getTabRenderer("BrowseHome", "singleColumnBrowseResultsRenderer");
                sectionListContents = tabRenderer["sectionListRenderer"].toObject()["contents"].toArray();
                if (sectionListContents.isEmpty())
                    throw InnertubeException("[BrowseHomeShelves] sectionListRenderer has no contents");
            }
            else
            {
                QJsonArray onResponseReceivedActions = QJsonDocument::fromJson(data).object()["onResponseReceivedActions"].toArray();
                if (onResponseReceivedActions.isEmpty())
                    throw InnertubeException("[BrowseHomeShelves] Continuation has no actions", InnertubeException::Minor); // this can just happen sometimes

                QJsonObject appendItemsAction = onResponseReceivedActions[0].toObject()["appendContinuationItemsAction"].toObject();
                if (appendItemsAction.isEmpty())
                    throw InnertubeException("[BrowseHomeShelves] Continuation has no appendContinuationItemsAction"); // now this shouldn't just happen

                sectionListContents = appendItemsAction["continuationItems"].toArray();
            }

            for (auto&& v : sectionListContents)
            {
                const QJsonObject& o = v.toObject();
                if (o.contains("shelfRenderer"))
                {
                    QJsonObject shelfRenderer = o["shelfRenderer"].toObject();
                    InnertubeObjects::InnertubeString shelfTitle(shelfRenderer["title"]);
                    shelves.append(shelfTitle);

                    QJsonArray shelfContents = shelfRenderer["content"].toObject()["horizontalListRenderer"].toObject()["items"].toArray();
                    for (auto&& v2 : shelfContents)
                    {
                        QJsonObject gridVideoRenderer = v2.toObject()["gridVideoRenderer"].toObject();
                        if (gridVideoRenderer.isEmpty()) continue;
                        videos.append(InnertubeObjects::Video(gridVideoRenderer, true, shelfTitle));
                    }
                }
                else if (o.contains("continuationItemRenderer"))
                {
                    continuationToken = o["continuationItemRenderer"].toObject()["continuationEndpoint"].toObject()["continuationCommand"].toObject()["token"].toString();
                }
            }
        };
    };
}

#endif // BROWSEHOMESHELVES_H
