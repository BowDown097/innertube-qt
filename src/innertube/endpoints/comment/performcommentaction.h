#pragma once
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/responses/comment/commentactionresponse.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Perform an action on a comment or community post, such as voting on a poll or giving a like.
     */
    struct PerformCommentAction : BaseEndpoint<"comment/perform_comment_action">
    {
        CommentActionResponse response;

        explicit PerformCommentAction(const QJsonValue& data);

        static QJsonObject createBody(const InnertubeContext* context, const QStringList& actions);

        /**
         * @param action  Supplied by ["performCommentActionEndpoint"]["action"] member of a service endpoint.
         */
        static QJsonObject createBody(const InnertubeContext* context, const QString& action);
    };
}
