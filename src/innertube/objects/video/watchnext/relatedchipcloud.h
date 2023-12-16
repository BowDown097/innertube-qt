#ifndef RELATEDCHIPCLOUD_H
#define RELATEDCHIPCLOUD_H
#include "innertube/objects/items/chipcloud/chipcloud.h"

namespace InnertubeObjects
{
    struct RelatedChipCloud : public ChipCloud
    {
        bool showProminentChips;

        RelatedChipCloud() = default;
        explicit RelatedChipCloud(const QJsonValue& relatedChipCloudRenderer)
            : ChipCloud(relatedChipCloudRenderer["content"]["chipCloudRenderer"]),
              showProminentChips(relatedChipCloudRenderer["showProminentChips"].toBool()) {}
    };
}

#endif // RELATEDCHIPCLOUD_H
