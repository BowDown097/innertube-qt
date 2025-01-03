#include "watchnextsecondaryresults.h"
#include <QJsonArray>
#include <QJsonObject>

namespace InnertubeObjects
{
    WatchNextSecondaryResults::WatchNextSecondaryResults(const QJsonValue& results)
    {
        const QJsonArray resultsArr = results.toArray();
        for (const QJsonValue& result : resultsArr)
        {
            if (result["compactVideoRenderer"].isObject())
            {
                feed.append(CompactVideo(result["compactVideoRenderer"]));
            }
            else if (result["continuationItemRenderer"].isObject())
            {
                feedContinuation = result["continuationItemRenderer"]["continuationEndpoint"]["continuationCommand"]["token"].toString();
            }
            else if (result["itemSectionRenderer"].isObject())
            {
                QString sectionIdentifier = result["itemSectionRenderer"]["sectionIdentifier"].toString();
                if (sectionIdentifier == "sid-wn-chips")
                {
                    const QJsonArray feedContents = result["itemSectionRenderer"]["contents"].toArray();
                    for (const QJsonValue& feedEntry : feedContents)
                    {
                        if (feedEntry["compactVideoRenderer"].isObject())
                            feed.append(CompactVideo(feedEntry["compactVideoRenderer"]));
                        else if (feedEntry["continuationItemRenderer"].isObject())
                            feedContinuation = feedEntry["continuationItemRenderer"]["continuationEndpoint"]["continuationCommand"]["token"].toString();
                    }
                }
            }
            else if (result["relatedChipCloudRenderer"].isObject())
            {
                relatedChipCloud.emplace(result["relatedChipCloudRenderer"]);
            }
        }
    }
}
