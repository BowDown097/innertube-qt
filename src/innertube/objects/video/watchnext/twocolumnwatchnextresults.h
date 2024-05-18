#pragma once
#include "innertube/objects/live_chat/livechat.h"
#include "watchnextprimaryresults.h"
#include "watchnextsecondaryresults.h"

namespace InnertubeObjects
{
    struct TwoColumnWatchNextResults
    {
        std::optional<LiveChat> liveChat;
        WatchNextPrimaryResults results;
        WatchNextSecondaryResults secondaryResults;

        TwoColumnWatchNextResults() = default;
        explicit TwoColumnWatchNextResults(const QJsonValue& twoColumnWatchNextResults)
            : liveChat(twoColumnWatchNextResults["conversationBar"]["liveChatRenderer"].isObject()
                           ? std::make_optional<LiveChat>(twoColumnWatchNextResults["conversationBar"]["liveChatRenderer"])
                           : std::nullopt),
              results(twoColumnWatchNextResults["results"]["results"]["contents"]),
              secondaryResults(twoColumnWatchNextResults["secondaryResults"]["secondaryResults"]["results"]) {}
    };
}
