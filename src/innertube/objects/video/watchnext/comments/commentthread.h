#ifndef COMMENTTHREAD_H
#define COMMENTTHREAD_H
#include "comment.h"
#include "commentreplies.h"

namespace InnertubeObjects
{
    struct CommentThread
    {
        Comment comment;
        bool isModeratedElqComment;
        QString renderingPriority;
        CommentReplies replies;

        CommentThread() = default;
        explicit CommentThread(const QJsonValue& commentThreadRenderer)
            : comment(commentThreadRenderer["comment"]["commentRenderer"]),
              isModeratedElqComment(commentThreadRenderer["isModeratedElqComment"].toBool()),
              renderingPriority(commentThreadRenderer["renderingPriority"].toString()),
              replies(commentThreadRenderer["replies"]["commentRepliesRenderer"]) {}
    };
}

#endif // COMMENTTHREAD_H
