#pragma once
#include "dislikebuttonviewmodel.h"
#include "dynamiclikecountupdatedata.h"
#include "likebuttonviewmodel.h"
#include "likecountentity.h"

namespace InnertubeObjects
{
    struct LikeDislikeViewModel
    {
        DislikeButtonViewModel dislikeButtonViewModel;
        DynamicLikeCountUpdateData dynamicLikeCountUpdateData;
        QString iconType;
        LikeButtonViewModel likeButtonViewModel;
        LikeCountEntity likeCountEntity;

        LikeDislikeViewModel() = default;
        explicit LikeDislikeViewModel(const QJsonValue& segmentedLikeDislikeButtonViewModel)
            : dislikeButtonViewModel(segmentedLikeDislikeButtonViewModel["dislikeButtonViewModel"]["dislikeButtonViewModel"]),
              dynamicLikeCountUpdateData(segmentedLikeDislikeButtonViewModel["dynamicLikeCountUpdateData"]),
              iconType(segmentedLikeDislikeButtonViewModel["iconType"].toString()),
              likeButtonViewModel(segmentedLikeDislikeButtonViewModel["likeButtonViewModel"]["likeButtonViewModel"]),
              likeCountEntity(segmentedLikeDislikeButtonViewModel["likeCountEntity"]) {}
    };
}
