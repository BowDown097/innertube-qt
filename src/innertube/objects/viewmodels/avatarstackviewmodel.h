#pragma once
#include "avatarviewmodel.h"

namespace InnertubeObjects
{
    struct AvatarStackViewModel
    {
        QList<AvatarViewModel> avatars;
        QString avatarClusterSize;
        QString layoutType;
        QJsonValue rendererContext;

        AvatarStackViewModel() = default;
        explicit AvatarStackViewModel(const QJsonValue& avatarStackViewModel);
    };
}