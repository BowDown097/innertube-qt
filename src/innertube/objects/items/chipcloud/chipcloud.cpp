#include "chipcloud.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    ChipCloud::ChipCloud(const QJsonValue& chipCloudRenderer)
        : horizontalScrollable(chipCloudRenderer["horizontalScrollable"].toBool()),
          nextButton(chipCloudRenderer["nextButton"]["buttonRenderer"]),
          previousButton(chipCloudRenderer["previousButton"]["buttonRenderer"])
    {
        const QJsonArray chipsJson = chipCloudRenderer["chips"].toArray();
        for (const QJsonValue& v : chipsJson)
            chips.append(InnertubeObjects::ChipCloudChip(v["chipCloudChipRenderer"]));
    }
}
