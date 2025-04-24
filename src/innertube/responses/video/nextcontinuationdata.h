#pragma once
#include "innertube/objects/video/compactvideo.h"
#include "innertube/objects/video/watchnext/comments/commentsheader.h"
#include "innertube/objects/video/watchnext/comments/commentthread.h"

namespace InnertubeEndpoints
{
    struct NextContinuationData
    {
        std::optional<InnertubeObjects::CommentsHeader> commentsHeader;
        QList<InnertubeObjects::CommentThread> commentThreads;
        QString continuationToken;
        QList<InnertubeObjects::CompactVideo> feed;

        NextContinuationData() = default;
        explicit NextContinuationData(const QJsonValue& onResponseReceivedEndpoints);
    };
}
