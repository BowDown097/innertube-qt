#ifndef COMMENTREPLIES_H
#define COMMENTREPLIES_H
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

#endif // COMMENTREPLIES_H
