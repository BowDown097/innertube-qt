#ifndef PERFORMCOMMENTACTION_H
#define PERFORMCOMMENTACTION_H
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/responses/comment/commentactionresponse.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Perform an action on a comment or community post, such as voting on a poll or giving a like.
     */
    class PerformCommentAction : public BaseEndpoint<"comment/perform_comment_action">
    {
        friend class ::InnerTube;
    public:
        CommentActionResponse response;
    protected:
        PerformCommentAction(InnertubeContext* context, InnertubeAuthStore* authStore, const QStringList& actions);
        PerformCommentAction(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& action)
            : PerformCommentAction(context, authStore, QStringList { action }) {}
    };
}

#endif // PERFORMCOMMENTACTION_H
