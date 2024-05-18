#pragma once
#include <QJsonValue>

namespace InnertubeObjects
{
    struct LikeCountEntity
    {
        QString expandedLikeCountIfDisliked;
        QString expandedLikeCountIfIndifferent;
        QString expandedLikeCountIfLiked;
        QString key;
        QString likeButtonA11yText;
        QString likeCountIfDisliked;
        QString likeCountIfDislikedNumber;
        QString likeCountIfIndifferent;
        QString likeCountIfIndifferentNumber;
        QString likeCountIfLiked;
        QString likeCountIfLikedNumber;
        QString likeCountLabel;
        QString sentimentFactoidA11yTextIfDisliked;
        QString sentimentFactoidA11yTextIfLiked;
        bool shouldExpandLikeCount;

        LikeCountEntity() = default;
        explicit LikeCountEntity(const QJsonValue& likeCountEntity)
            : expandedLikeCountIfDisliked(likeCountEntity["expandedLikeCountIfDisliked"]["content"].toString()),
              expandedLikeCountIfIndifferent(likeCountEntity["expandedLikeCountIfIndifferent"]["content"].toString()),
              expandedLikeCountIfLiked(likeCountEntity["expandedLikeCountIfLiked"]["content"].toString()),
              key(likeCountEntity["key"].toString()),
              likeButtonA11yText(likeCountEntity["likeButtonA11yText"]["content"].toString()),
              likeCountIfDisliked(likeCountEntity["likeCountIfDisliked"]["content"].toString()),
              likeCountIfDislikedNumber(likeCountEntity["likeCountIfDislikedNumber"].toString()),
              likeCountIfIndifferent(likeCountEntity["likeCountIfIndifferent"]["content"].toString()),
              likeCountIfIndifferentNumber(likeCountEntity["likeCountIfIndifferentNumber"].toString()),
              likeCountIfLiked(likeCountEntity["likeCountIfLiked"]["content"].toString()),
              likeCountIfLikedNumber(likeCountEntity["likeCountIfLikedNumber"].toString()),
              likeCountLabel(likeCountEntity["likeCountLabel"]["content"].toString()),
              sentimentFactoidA11yTextIfDisliked(likeCountEntity["sentimentFactoidA11yTextIfDisliked"]["content"].toString()),
              sentimentFactoidA11yTextIfLiked(likeCountEntity["sentimentFactoidA11yTextIfLiked"]["content"].toString()) {}
    };
}
