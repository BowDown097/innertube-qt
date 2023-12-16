#include "watchnextprimaryresults.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    WatchNextPrimaryResults::WatchNextPrimaryResults(const QJsonValue& contents)
    {
        const QJsonArray contentsArr = contents.toArray();
        for (const QJsonValue& result : contentsArr)
        {
            if (result["itemSectionRenderer"].isObject())
            {
                QJsonValue sectionItem = result["itemSectionRenderer"]["contents"][0];
                if (sectionItem["clarificationRenderer"].isObject())
                    clarification.emplace(sectionItem["clarificationRenderer"]);
                else if (sectionItem["commentsEntryPointHeaderRenderer"].isObject())
                    commentsEntryPointHeader.emplace(sectionItem["commentsEntryPointHeaderRenderer"]);
                else if (sectionItem["continuationItemRenderer"].isObject())
                    commentsSectionContinuation = sectionItem["continuationItemRenderer"]["continuationEndpoint"]["continuationCommand"]["token"].toString();
            }
            else if (result["videoPrimaryInfoRenderer"].isObject())
            {
                primaryInfo = InnertubeObjects::VideoPrimaryInfo(result["videoPrimaryInfoRenderer"]);
            }
            else if (result["videoSecondaryInfoRenderer"].isObject())
            {
                secondaryInfo = InnertubeObjects::VideoSecondaryInfo(result["videoSecondaryInfoRenderer"]);
            }
        }
    }
}
