#pragma once
#include "innertube/objects/images/responsiveimage.h"

namespace InnertubeObjects
{
    struct AvatarViewModel
    {
        QString avatarImageSize;
        ResponsiveImage image;

        AvatarViewModel() = default;
        explicit AvatarViewModel(const QJsonValue& avatarViewModel)
            : avatarImageSize(avatarViewModel["avatarImageSize"].toString()),
              image(avatarViewModel["image"]["sources"]) {}
    };
}
