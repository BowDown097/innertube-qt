#include "browsetrending.h"
#include "innertube/innertubeexception.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    BrowseTrending::BrowseTrending(InnertubeContext* context, InnertubeAuthStore* authStore)
        : BaseBrowseEndpoint("FEtrending", context, authStore)
    {
        QJsonValue tabRenderer = getTabRenderer("BrowseTrending");
        const QJsonArray sectionListRenderer = tabRenderer["sectionListRenderer"]["contents"].toArray();
        if (sectionListRenderer.isEmpty())
            throw InnertubeException("[BrowseTrending] sectionListRenderer has no contents");

        for (const QJsonValue& v : sectionListRenderer)
        {
            const QJsonArray itemSectionContents = v["itemSectionRenderer"]["contents"].toArray();
            if (itemSectionContents.isEmpty())
                throw InnertubeException("[BrowseTrending] itemSectionRenderer not found or has no content");

            QJsonValue shelfRenderer = itemSectionContents[0]["shelfRenderer"];
            const QJsonObject shelfContent = shelfRenderer["content"].toObject();
            if (shelfContent.isEmpty()) continue;

            InnertubeObjects::InnertubeString shelfTitle = shelfRenderer["title"].isObject()
                    ? InnertubeObjects::InnertubeString(shelfRenderer["title"])
                    : InnertubeObjects::InnertubeString(QString("Now"));
            if (!response.shelves.contains(shelfTitle))
                response.shelves.append(shelfTitle);

            const QStringList keys = shelfContent.keys();
            const QString appropriateList = keys.first();
            const QJsonArray shelfContents = shelfContent[appropriateList]["items"].toArray();
            for (const QJsonValue& v2 : shelfContents)
            {
                const QString rendererType = appropriateList == "expandedShelfContentsRenderer" ? "videoRenderer" : "gridVideoRenderer";
                if (!v2[rendererType].isObject()) continue;
                response.videos.append(InnertubeObjects::Video(v2[rendererType], rendererType == "gridVideoRenderer", shelfTitle));
            }
        }
    }
}
