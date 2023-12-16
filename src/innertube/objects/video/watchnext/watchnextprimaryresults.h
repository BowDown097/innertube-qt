#ifndef WATCHNEXTPRIMARYRESULTS_H
#define WATCHNEXTPRIMARYRESULTS_H
#include "clarification.h"
#include "comments/entrypoint/commentsentrypointheader.h"
#include "primaryinfo/videoprimaryinfo.h"
#include "secondaryinfo/videosecondaryinfo.h"

namespace InnertubeObjects
{
    struct WatchNextPrimaryResults
    {
        std::optional<Clarification> clarification;
        std::optional<CommentsEntryPointHeader> commentsEntryPointHeader;
        std::optional<QString> commentsSectionContinuation;
        VideoPrimaryInfo primaryInfo;
        VideoSecondaryInfo secondaryInfo;

        WatchNextPrimaryResults() = default;
        explicit WatchNextPrimaryResults(const QJsonValue& contents);
    };
}

#endif // WATCHNEXTPRIMARYRESULTS_H
