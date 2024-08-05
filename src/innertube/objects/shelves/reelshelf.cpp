#include "reelshelf.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    ReelShelf::ReelShelf(const QJsonValue& reelShelfRenderer)
        : button(reelShelfRenderer["button"]["menuRenderer"]),
          icon(reelShelfRenderer["icon"]["iconType"].toString()),
          title(reelShelfRenderer["title"])
    {
        const QJsonArray itemsArr = reelShelfRenderer["items"].toArray();
        for (const QJsonValue& item : itemsArr)
            items.append(Reel(item["reelItemRenderer"]));
    }
}
