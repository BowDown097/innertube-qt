#pragma once
#include "innertube/objects/viewmodels/togglebuttonviewmodel.h"

namespace InnertubeObjects
{
    struct DislikeButtonViewModel
    {
        QString dislikeEntityKey;
        ToggleButtonViewModel toggleButtonViewModel;

        DislikeButtonViewModel() = default;
        explicit DislikeButtonViewModel(const QJsonValue& dislikeButtonViewModel)
            : dislikeEntityKey(dislikeButtonViewModel["dislikeEntityKey"].toString()),
              toggleButtonViewModel(dislikeButtonViewModel["toggleButtonViewModel"]["toggleButtonViewModel"]) {}
    };
}
