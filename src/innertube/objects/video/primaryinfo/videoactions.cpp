#include "videoactions.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    VideoActions::VideoActions(const QJsonValue& menuRenderer)
        : accessibilityLabel(menuRenderer["accessibility"]["accessibilityData"]["label"].toString()),
          segmentedLikeDislikeButtonViewModel(menuRenderer["topLevelButtons"][0]["segmentedLikeDislikeButtonViewModel"])
    {
        const QJsonArray flexibleItemsJson = menuRenderer["flexibleItems"].toArray();
        for (const QJsonValue& v : flexibleItemsJson)
            flexibleItems.append(MenuFlexibleItem(v["menuFlexibleItemRenderer"]));

        const QJsonArray itemsJson = menuRenderer["items"].toArray();
        for (const QJsonValue& v : itemsJson)
            items.append(MenuServiceItem(v["menuServiceItemRenderer"]));
    }
}
