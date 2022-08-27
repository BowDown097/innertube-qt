#ifndef BROWSEHOME_H
#define BROWSEHOME_H
#include <endpoints/base/basebrowseendpoint.h>
#include <objects/video/video.h>

namespace InnertubeEndpoints
{
    class BrowseHome : public BaseBrowseEndpoint
    {
    public:
        QVector<InnertubeObjects::Video> videos;
    private:
        friend class ::InnerTube;
        explicit BrowseHome(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore) : BaseBrowseEndpoint("FEwhat_to_watch", context, easy, authStore)
        {
            QJsonObject contents = QJsonDocument::fromJson(data).object()["contents"].toObject();
            if (contents.isEmpty())
                throw InnertubeException("[BrowseHome] contents not found");

            QJsonObject resultsRenderer = contents["twoColumnBrowseResultsRenderer"].toObject();
            if (resultsRenderer.isEmpty())
                throw InnertubeException("[BrowseHome] twoColumnBrowseResultsRenderer not found");

            QJsonArray tabs = resultsRenderer["tabs"].toArray();
            if (tabs.count() != 1)
                throw InnertubeException(QStringLiteral("[BrowseHome] Expected 1 element in tabs, got %1").arg(tabs.count()));

            QJsonObject tabRenderer = tabs[0].toObject()["tabRenderer"].toObject()["content"].toObject();
            if (tabRenderer.isEmpty())
                throw InnertubeException("[BrowseHome] tabRenderer not found");
            if (!tabRenderer.contains("richGridRenderer"))
                throw InnertubeException("[BrowseHome] No grid in tabRenderer");

            QJsonArray gridContents = tabRenderer["richGridRenderer"].toObject()["contents"].toArray();
            for (auto&& v : gridContents)
            {
                QJsonObject richItemRenderer = v.toObject()["richItemRenderer"].toObject();
                if (richItemRenderer.isEmpty()) continue;

                QJsonObject videoRenderer = richItemRenderer["content"].toObject()["videoRenderer"].toObject();
                if (videoRenderer.isEmpty()) continue;

                videos.append(InnertubeObjects::Video(videoRenderer, false));
            }
        };
    };
}

#endif // BROWSEHOME_H
