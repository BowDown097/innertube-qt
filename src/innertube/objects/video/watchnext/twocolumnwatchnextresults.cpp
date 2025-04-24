#include "twocolumnwatchnextresults.h"

namespace InnertubeObjects
{
    TwoColumnWatchNextResults::TwoColumnWatchNextResults(const QJsonValue& twoColumnWatchNextResults)
        : autoplay(twoColumnWatchNextResults["autoplay"]["autoplay"]),
          results(twoColumnWatchNextResults["results"]["results"]["contents"]),
          secondaryResults(twoColumnWatchNextResults["secondaryResults"]["secondaryResults"]["results"])
    {
        if (const QJsonValue lcr = twoColumnWatchNextResults["conversationBar"]["liveChatRenderer"]; lcr.isObject())
            conversationBar.emplace(lcr);
    }
}
