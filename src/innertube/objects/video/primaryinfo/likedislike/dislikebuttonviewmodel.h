#ifndef DISLIKEBUTTONVIEWMODEL_H
#define DISLIKEBUTTONVIEWMODEL_H
#include "innertube/objects/viewmodels/togglebuttonviewmodel.h"

namespace InnertubeObjects
{
    class DislikeButtonViewModel
    {
    public:
        QString dislikeEntityKey;
        ToggleButtonViewModel toggleButtonViewModel;

        DislikeButtonViewModel() = default;
        explicit DislikeButtonViewModel(const QJsonValue& dislikeButtonViewModel)
            : dislikeEntityKey(dislikeButtonViewModel["dislikeEntityKey"].toString()),
              toggleButtonViewModel(dislikeButtonViewModel["toggleButtonViewModel"]["toggleButtonViewModel"]) {}
    };
}

#endif // DISLIKEBUTTONVIEWMODEL_H
