#include "videoactions.h"
#include "jsonutil.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    VideoActions::VideoActions(const QJsonValue& menuRenderer)
        : accessibilityLabel(menuRenderer["accessibility"]["accessibilityData"]["label"].toString()),
          dislikeButton(JsonUtil::rfind("dislikeButton", menuRenderer["topLevelButtons"])["toggleButtonRenderer"]),
          likeButton(JsonUtil::rfind("likeButton", menuRenderer["topLevelButtons"])["toggleButtonRenderer"])
    {
        const QJsonArray flexibleItemsJson = menuRenderer["flexibleItems"].toArray();
        for (const QJsonValue& v : flexibleItemsJson)
            flexibleItems.append(MenuFlexibleItem(v["menuFlexibleItemRenderer"]));

        const QJsonArray itemsJson = menuRenderer["items"].toArray();
        for (const QJsonValue& v : itemsJson)
            items.append(MenuServiceItem(v["menuServiceItemRenderer"]));

        const QJsonArray topLevelButtonsJson = menuRenderer["topLevelButtons"].toArray();
        QJsonArray::const_iterator shareTLB = std::ranges::find_if(topLevelButtonsJson, [](const QJsonValue& v)
                                                                { return v["buttonRenderer"]["icon"]["iconType"].toString() == "SHARE"; });
        if (shareTLB != topLevelButtonsJson.cend())
        {
            const QJsonValue& shareTLBVal = *shareTLB;
            shareButton = Button(shareTLBVal["buttonRenderer"]);
        }
    }
}
