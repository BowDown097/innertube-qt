#include "browsetrending.h"
#include "innertube/innertubeexception.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    BrowseTrending::BrowseTrending(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore)
        : BaseBrowseEndpoint("FEtrending", context, easy, authStore)
    {
        QJsonObject tabRenderer = getTabRenderer("BrowseTrending");
        QJsonArray sectionListRenderer = tabRenderer["sectionListRenderer"].toObject()["contents"].toArray();
        if (sectionListRenderer.isEmpty())
            throw InnertubeException("[BrowseTrending] sectionListRenderer has no contents");

        for (auto&& v : sectionListRenderer)
        {
            QJsonArray itemSectionContents = v.toObject()["itemSectionRenderer"].toObject()["contents"].toArray();
            if (itemSectionContents.isEmpty())
                throw InnertubeException("[BrowseTrending] itemSectionRenderer not found or has no content");

            QJsonObject shelfRenderer = itemSectionContents[0].toObject()["shelfRenderer"].toObject();
            QJsonObject shelfContent = shelfRenderer["content"].toObject();
            if (shelfContent.isEmpty()) continue;

            InnertubeObjects::InnertubeString shelfTitle = shelfRenderer.contains("title")
                    ? InnertubeObjects::InnertubeString(shelfRenderer["title"])
                    : InnertubeObjects::InnertubeString(QString("Now"));
            if (!response.shelves.contains(shelfTitle))
                response.shelves.append(shelfTitle);

            const QStringList keys = shelfContent.keys();
            QString appropriateList = keys.first();
            QJsonArray shelfContents = shelfContent[appropriateList].toObject()["items"].toArray();
            for (auto&& v2 : shelfContents)
            {
                QString rendererType = appropriateList == "expandedShelfContentsRenderer" ? "videoRenderer" : "gridVideoRenderer";
                QJsonObject videoRenderer = v2.toObject()[rendererType].toObject();
                if (videoRenderer.isEmpty()) continue;
                response.videos.append(InnertubeObjects::Video(videoRenderer, rendererType == "gridVideoRenderer", shelfTitle));
            }
        }
    }
}
