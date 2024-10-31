#include "browsetrending.h"
#include "innertube/innertubeexception.h"
#include "jsonutil.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    BrowseTrending::BrowseTrending(const InnertubeContext* context, const InnertubeAuthStore* authStore)
        : BaseBrowseEndpoint("FEtrending", context, authStore)
    {
        const QJsonValue tabRenderer = getTabRenderer("BrowseTrending");
        const QJsonArray sectionListRenderer = tabRenderer["sectionListRenderer"]["contents"].toArray();
        if (sectionListRenderer.isEmpty())
            throw InnertubeException("[BrowseTrending] sectionListRenderer has no contents");

        for (const QJsonValue& section : sectionListRenderer)
        {
            const QJsonArray itemSectionContents = section["itemSectionRenderer"]["contents"].toArray();
            if (itemSectionContents.isEmpty())
                throw InnertubeException("[BrowseTrending] itemSectionRenderer not found or has no content");

            for (const QJsonValue& sectionItem : itemSectionContents)
            {
                if (const QJsonValue reelShelf = sectionItem["reelShelfRenderer"]; reelShelf.isObject())
                {
                    response.contents.append(InnertubeObjects::ReelShelf(reelShelf));
                }
                else if (const QJsonValue shelf = sectionItem["shelfRenderer"]; shelf.isObject())
                {
                    if (const QJsonValue expanded = shelf["content"]["expandedShelfContentsRenderer"]["items"]; expanded.isArray())
                    {
                        const QJsonArray expandedArr = expanded.toArray();
                        QList<InnertubeObjects::Video> videoList;
                        videoList.reserve(expandedArr.size());

                        for (const QJsonValue& item : expandedArr)
                        {
                            if (const QJsonValue gridVideo = item["gridVideoRenderer"]; gridVideo.isObject())
                                videoList.append(InnertubeObjects::Video(gridVideo));
                            else if (const QJsonValue video = item["videoRenderer"]; video.isObject())
                                videoList.append(InnertubeObjects::Video(video));
                        }

                        if (!videoList.isEmpty())
                            response.contents.append(InnertubeObjects::StandardVideoShelf(shelf, std::move(videoList)));
                        else if (QString itemKey = JsonUtil::getFirstKey(expanded); !itemKey.isEmpty())
                            qWarning() << QStringLiteral("[BrowseTrending] Unexpected key in expandedShelfContentsRenderer: %1").arg(itemKey);
                    }
                    else if (const QJsonValue list = shelf["content"]["horizontalListRenderer"]; list.isObject())
                    {
                        // it shouldn't be possible for there to be multiple types in the same horizontalList here, so this will suffice.
                        QString itemKey = JsonUtil::getFirstKey(list["items"]);
                        if (itemKey == "gridVideoRenderer" || itemKey == "videoRenderer")
                        {
                            response.contents.append(InnertubeObjects::HorizontalVideoShelf(shelf,
                                InnertubeObjects::HorizontalList<InnertubeObjects::Video>(list, itemKey)));
                        }
                        else
                        {
                            qWarning() << QStringLiteral("[BrowseTrending] Unexpected key in horizontalListRenderer: %1").arg(itemKey);
                        }
                    }
                }
            }
        }
    }
}
