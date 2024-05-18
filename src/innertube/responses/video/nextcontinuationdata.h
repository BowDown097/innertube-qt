#pragma once
#include "innertube/objects/video/video.h"
#include "innertube/objects/video/watchnext/comments/commentsheader.h"
#include "innertube/objects/video/watchnext/comments/commentthread.h"

namespace InnertubeEndpoints
{
    struct NextContinuationData
    {
        std::optional<InnertubeObjects::CommentsHeader> commentsHeader;
        QList<InnertubeObjects::CommentThread> commentThreads;
        std::optional<QString> continuationToken;
        QList<InnertubeObjects::Video> feed;

        NextContinuationData() = default;
        explicit NextContinuationData(const QJsonValue& onResponseReceivedEndpoints);
    };
}
