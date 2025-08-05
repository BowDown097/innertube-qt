#pragma once
#include "innertube/objects/video/watchnext/comments/commentsheader.h"
#include "innertube/objects/video/watchnext/comments/commentthread.h"
#include "innertube/objects/viewmodels/lockupviewmodel.h"

namespace InnertubeEndpoints
{
    struct NextContinuationData
    {
        std::optional<InnertubeObjects::CommentsHeader> commentsHeader;
        QList<InnertubeObjects::CommentThread> commentThreads;
        QString continuationToken;
        QList<InnertubeObjects::LockupViewModel> feed;

        NextContinuationData() = default;
        explicit NextContinuationData(const QJsonValue& onResponseReceivedEndpoints);
    };
}
