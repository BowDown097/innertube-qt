#pragma once
#include "innertube/objects/items/button.h"

namespace InnertubeObjects
{
    struct CommentReplies
    {
        std::optional<QString> continuationToken;
        Button hideReplies;
        QString targetId;
        Button viewReplies;

        CommentReplies() = default;
        explicit CommentReplies(const QJsonValue& commentRepliesRenderer);
    };
}
