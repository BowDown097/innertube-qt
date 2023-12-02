#ifndef LIKEBUTTONVIEWMODEL_H
#define LIKEBUTTONVIEWMODEL_H
#include "innertube/objects/viewmodels/togglebuttonviewmodel.h"

namespace InnertubeObjects
{
    class LikeButtonViewModel
    {
    public:
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

#endif // LIKEBUTTONVIEWMODEL_H
