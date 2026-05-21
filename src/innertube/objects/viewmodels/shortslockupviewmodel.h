#pragma once
#include "thumbnailviewmodel.h"

namespace InnertubeObjects
{
    struct ShortsLockupViewModel
    {
        QString accessibilityText;
        QString entityId;
        int indexInCollection;
        QJsonValue inlinePlayerData;
        QJsonValue menuOnTap;
        QString menuOnTapA11yLabel;
        QJsonValue onTap;
        QString primaryText;
        QString secondaryText;
        ThumbnailViewModel thumbnailViewModel;
        QString videoId;

        explicit ShortsLockupViewModel(const QJsonValue& shortsLockupViewModel)
            : accessibilityText(shortsLockupViewModel["accessibilityText"].toString()),
              entityId(shortsLockupViewModel["entityId"].toString()),
              indexInCollection(shortsLockupViewModel["indexInCollection"].toInt()),
              inlinePlayerData(shortsLockupViewModel["inlinePlayerData"]),
              menuOnTap(shortsLockupViewModel["menuOnTap"]),
              menuOnTapA11yLabel(shortsLockupViewModel["menuOnTapA11yLabel"].toString()),
              onTap(shortsLockupViewModel["onTap"]),
              primaryText(shortsLockupViewModel["overlayMetadata"]["primaryText"]["content"].toString()),
              secondaryText(shortsLockupViewModel["overlayMetadata"]["secondaryText"]["content"].toString()),
              thumbnailViewModel(shortsLockupViewModel["thumbnailViewModel"]["thumbnailViewModel"]),
              videoId(onTap["innertubeCommand"]["reelWatchEndpoint"]["videoId"].toString()) {}
    };
}
