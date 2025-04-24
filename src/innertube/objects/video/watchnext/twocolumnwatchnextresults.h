#pragma once
#include "autoplaydata.h"
#include "livechat.h"
#include "watchnextprimaryresults.h"
#include "watchnextsecondaryresults.h"

namespace InnertubeObjects
{
    struct TwoColumnWatchNextResults
    {
        AutoplayData autoplay;
        std::optional<LiveChat> conversationBar;
        WatchNextPrimaryResults results;
        WatchNextSecondaryResults secondaryResults;

        TwoColumnWatchNextResults() = default;
        explicit TwoColumnWatchNextResults(const QJsonValue& twoColumnWatchNextResults);
    };
}
