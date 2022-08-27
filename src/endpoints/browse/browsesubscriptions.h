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
        QVector<InnertubeObjects::Video> videos;
    private:
        explicit BrowseSubscriptions(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore) : BaseBrowseEndpoint("FEsubscriptions", context, easy, authStore)
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

            QJsonArray sectionListRenderer = tabRenderer["sectionListRenderer"].toObject()["contents"].toArray();
            if (sectionListRenderer.count() < 1)
                throw InnertubeException("[BrowseSubscriptions] sectionListRenderer has no contents");

            QJsonArray itemSectionContents = sectionListRenderer[0].toObject()["itemSectionRenderer"].toObject()["contents"].toArray();
            if (itemSectionContents.isEmpty())
                throw InnertubeException("[BrowseSubscriptions] itemSectionRenderer not found or has no content");

            for (auto&& v : itemSectionContents)
            {
                QJsonObject shelfRenderer = v.toObject()["shelfRenderer"].toObject();
                if (shelfRenderer.isEmpty()) continue;

                QJsonArray gridContents = shelfRenderer["content"].toObject()["gridRenderer"].toObject()["items"].toArray();
                for (auto&& v2 : gridContents)
                {
                    QJsonObject gridVideoRenderer = v2.toObject()["gridVideoRenderer"].toObject();
                    if (gridVideoRenderer.isEmpty()) continue;

                    videos.append(InnertubeObjects::Video(gridVideoRenderer, true));
                }
            }
        }
    };
}

#endif // BROWSESUBSCRIPTIONS_H
