#include "nextcontinuationdata.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    NextContinuationData::NextContinuationData(const QJsonValue& onResponseReceivedEndpoints)
    {
        const QJsonArray endpointsArr = onResponseReceivedEndpoints.toArray();
        for (const QJsonValue& endpoint : endpointsArr)
        {
            if (endpoint["appendContinuationItemsAction"].isObject())
            {
                const QJsonArray continuationItems = endpoint["appendContinuationItemsAction"]["continuationItems"].toArray();
                for (const QJsonValue& continuationItem : continuationItems)
                {
                    if (continuationItem["compactVideoRenderer"].isObject())
                    {
                        feed.append(InnertubeObjects::CompactVideo(continuationItem["compactVideoRenderer"]));
                    }
                    else if (continuationItem["continuationItemRenderer"].isObject())
                    {
                        continuationToken = continuationItem["continuationItemRenderer"]["continuationEndpoint"]
                                                            ["continuationCommand"]["token"].toString();
                    }
                }
            }
            else if (endpoint["reloadContinuationItemsCommand"].isObject())
            {
                QJsonValue command = endpoint["reloadContinuationItemsCommand"];
                QString slot = command["slot"].toString();

                if (slot == "RELOAD_CONTINUATION_SLOT_HEADER")
                {
                    commentsHeader.emplace(command["continuationItems"][0]["commentsHeaderRenderer"]);
                }
                else if (slot == "RELOAD_CONTINUATION_SLOT_BODY")
                {
                    const QJsonArray continuationItems = command["continuationItems"].toArray();
                    for (const QJsonValue& continuationItem : continuationItems)
                    {
                        if (continuationItem["commentThreadRenderer"].isObject())
                        {
                            commentThreads.append(InnertubeObjects::CommentThread(continuationItem["commentThreadRenderer"]));
                        }
                        else if (continuationItem["continuationItemRenderer"].isObject())
                        {
                            continuationToken = continuationItem["continuationItemRenderer"]["continuationEndpoint"]
                                                                ["continuationCommand"]["token"].toString();
                        }
                    }
                }
            }
        }
    }
}
