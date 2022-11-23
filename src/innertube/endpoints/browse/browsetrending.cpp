#include "browsetrending.h"
#include "innertube/innertubeexception.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    BrowseTrending::BrowseTrending(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore)
        : BaseBrowseEndpoint("FEtrending", context, easy, authStore)
    {
        QJsonObject tabRenderer = getTabRenderer("BrowseTrending");
        const QJsonArray sectionListRenderer = tabRenderer["sectionListRenderer"].toObject()["contents"].toArray();
        if (sectionListRenderer.isEmpty())
            throw InnertubeException("[BrowseTrending] sectionListRenderer has no contents");

        for (const QJsonValue& v : sectionListRenderer)
        {
            const QJsonArray itemSectionContents = v["itemSectionRenderer"]["contents"].toArray();
            if (itemSectionContents.isEmpty())
                throw InnertubeException("[BrowseTrending] itemSectionRenderer not found or has no content");

            const QJsonObject shelfRenderer = itemSectionContents[0].toObject()["shelfRenderer"].toObject();
            const QJsonObject shelfContent = shelfRenderer["content"].toObject();
            if (shelfContent.isEmpty()) continue;

            InnertubeObjects::InnertubeString shelfTitle = shelfRenderer.contains("title")
                    ? InnertubeObjects::InnertubeString(shelfRenderer["title"])
                    : InnertubeObjects::InnertubeString(QString("Now"));
            if (!response.shelves.contains(shelfTitle))
                response.shelves.append(shelfTitle);

            const QStringList keys = shelfContent.keys();
            const QString appropriateList = keys.first();
            const QJsonArray shelfContents = shelfContent[appropriateList]["items"].toArray();
            for (const QJsonValue& v2 : shelfContents)
            {
                QString rendererType = appropriateList == "expandedShelfContentsRenderer" ? "videoRenderer" : "gridVideoRenderer";
                const QJsonObject videoRenderer = v2[rendererType].toObject();
                if (videoRenderer.isEmpty()) continue;
                response.videos.append(InnertubeObjects::Video(videoRenderer, rendererType == "gridVideoRenderer", shelfTitle));
            }
        }
    }
}
