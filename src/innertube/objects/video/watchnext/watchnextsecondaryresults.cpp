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
            if (const QJsonValue itemSectionRenderer = result["itemSectionRenderer"];
                itemSectionRenderer.isObject())
            {
                if (itemSectionRenderer["sectionIdentifier"].toString() == "sid-wn-chips")
                {
                    const QJsonArray feedContents = itemSectionRenderer["contents"].toArray();
                    for (const QJsonValue& feedEntry : feedContents)
                    {
                        if (const QJsonValue lockupViewModel = feedEntry["lockupViewModel"];
                            lockupViewModel.isObject())
                        {
                            feed.append(LockupViewModel(lockupViewModel));
                        }
                        else if (const QJsonValue adSlotRenderer = feedEntry["adSlotRenderer"];
                                 adSlotRenderer.isObject())
                        {
                            feed.append(AdSlot(adSlotRenderer));
                        }
                        else if (const QJsonValue continuationItemRenderer = feedEntry["continuationItemRenderer"];
                                 continuationItemRenderer.isObject())
                        {
                            feedContinuation = continuationItemRenderer["continuationEndpoint"]["continuationCommand"]["token"].toString();
                        }
                    }
                }
            }
            else if (const QJsonValue relatedChipCloudRenderer = result["relatedChipCloudRenderer"];
                     relatedChipCloudRenderer.isObject())
            {
                relatedChipCloud.emplace(relatedChipCloudRenderer);
            }
        }
    }
}
