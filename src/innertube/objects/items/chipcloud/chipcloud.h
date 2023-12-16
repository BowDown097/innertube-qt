#ifndef CHIPCLOUD_H
#define CHIPCLOUD_H
#include "chipcloudchip.h"
#include "innertube/objects/items/button.h"

namespace InnertubeObjects
{
    struct ChipCloud
    {
        QList<ChipCloudChip> chips;
        bool horizontalScrollable;
        Button nextButton;
        Button previousButton;

        ChipCloud() = default;
        explicit ChipCloud(const QJsonValue& chipCloudRenderer);
    };
}

#endif // CHIPCLOUD_H
