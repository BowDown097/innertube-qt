#pragma once
#include "clarification.h"
#include "comments/entrypoint/commentsentrypointheader.h"
#include "innertube/objects/viewmodels/videometadatacarouselviewmodel.h"
#include "primaryinfo/videoprimaryinfo.h"
#include "secondaryinfo/videosecondaryinfo.h"

namespace InnertubeObjects
{
    struct WatchNextPrimaryResults
    {
        std::optional<Clarification> clarification;
        std::optional<CommentsEntryPointHeader> commentsEntryPointHeader;
        QString commentsSectionContinuation;
        VideoPrimaryInfo primaryInfo;
        VideoSecondaryInfo secondaryInfo;
        std::optional<VideoMetadataCarouselViewModel> videoMetadataCarousel;

        WatchNextPrimaryResults() = default;
        explicit WatchNextPrimaryResults(const QJsonValue& contents);
    };
}
