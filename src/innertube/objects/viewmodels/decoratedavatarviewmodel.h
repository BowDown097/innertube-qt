#pragma once
#include "avatarviewmodel.h"

namespace InnertubeObjects
{
    struct DecoratedAvatarViewModel
    {
        QString a11yLabel;
        AvatarViewModel avatar;
        QJsonValue rendererContext;

        DecoratedAvatarViewModel() = default;
        explicit DecoratedAvatarViewModel(const QJsonValue& decoratedAvatarViewModel)
            : a11yLabel(decoratedAvatarViewModel["a11yLabel"].toString()),
              avatar(decoratedAvatarViewModel["avatar"]["avatarViewModel"]),
              rendererContext(decoratedAvatarViewModel["rendererContext"]) {}
    };
}
