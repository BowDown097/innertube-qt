#include "nextcontinuationdata.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    NextContinuationData::NextContinuationData(const QJsonValue& onResponseReceivedEndpoints)
    {
        const QJsonArray endpointsArr = onResponseReceivedEndpoints.toArray();
        for (const QJsonValue& endpoint : endpointsArr)
        {
            if (const QJsonValue continuationItemsAction = endpoint["appendContinuationItemsAction"];
                continuationItemsAction.isObject())
            {
                const QJsonArray continuationItems = continuationItemsAction["continuationItems"].toArray();
                for (const QJsonValue& continuationItem : continuationItems)
                {
                    if (const QJsonValue lockupViewModel = continuationItem["lockupViewModel"];
                        lockupViewModel.isObject())
                    {
                        feed.emplaceBack(lockupViewModel);
                    }
                    else if (const QJsonValue continuation = continuationItem["continuationItemRenderer"];
                             continuation.isObject())
                    {
                        continuationToken = continuation["continuationEndpoint"]["continuationCommand"]["token"].toString();
                    }
                }
            }
            else if (const QJsonValue reloadAction = endpoint["reloadContinuationItemsCommand"]; reloadAction.isObject())
            {
                const QString slot = reloadAction["slot"].toString();
                if (slot == "RELOAD_CONTINUATION_SLOT_HEADER")
                {
                    commentsHeader.emplace(reloadAction["continuationItems"][0]["commentsHeaderRenderer"]);
                }
                else if (slot == "RELOAD_CONTINUATION_SLOT_BODY")
                {
                    const QJsonArray continuationItems = reloadAction["continuationItems"].toArray();
                    for (const QJsonValue& continuationItem : continuationItems)
                    {
                        if (const QJsonValue commentThreadRenderer = continuationItem["commentThreadRenderer"];
                            commentThreadRenderer.isObject())
                        {
                            commentThreads.append(InnertubeObjects::CommentThread(commentThreadRenderer));
                        }
                        else if (const QJsonValue continuation = continuationItem["continuationItemRenderer"];
                                 continuation.isObject())
                        {
                            continuationToken = continuation["continuationEndpoint"]["continuationCommand"]["token"].toString();
                        }
                    }
                }
            }
        }
    }
}
