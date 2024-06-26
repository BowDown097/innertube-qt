#pragma once
#include "innertube/objects/viewmodels/togglebuttonviewmodel.h"

namespace InnertubeObjects
{
    struct LikeButtonViewModel
    {
        QString likeStatus;
        QString likeStatusEntityKey;
        ToggleButtonViewModel toggleButtonViewModel;

        LikeButtonViewModel() = default;
        explicit LikeButtonViewModel(const QJsonValue& likeButtonViewModel)
            : likeStatus(likeButtonViewModel["likeStatusEntity"]["likeStatus"].toString()),
              likeStatusEntityKey(likeButtonViewModel["likeStatusEntityKey"].toString()),
              toggleButtonViewModel(likeButtonViewModel["toggleButtonViewModel"]["toggleButtonViewModel"]) {}
    };
}
