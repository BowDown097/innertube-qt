#pragma once
#include "innertube/objects/items/chipcloud/chipcloud.h"

namespace InnertubeObjects
{
    struct RelatedChipCloud : ChipCloud
    {
        bool showProminentChips{};

        RelatedChipCloud() = default;
        explicit RelatedChipCloud(const QJsonValue& relatedChipCloudRenderer)
            : ChipCloud(relatedChipCloudRenderer["content"]["chipCloudRenderer"]),
              showProminentChips(relatedChipCloudRenderer["showProminentChips"].toBool()) {}
    };
}
