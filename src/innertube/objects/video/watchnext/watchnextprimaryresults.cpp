#include "watchnextprimaryresults.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    WatchNextPrimaryResults::WatchNextPrimaryResults(const QJsonValue& contents)
    {
        const QJsonArray contentsArr = contents.toArray();
        for (const QJsonValue& result : contentsArr)
        {
            if (const QJsonValue itemSectionRenderer = result["itemSectionRenderer"];
                itemSectionRenderer.isObject())
            {
                const QJsonValue sectionItem = itemSectionRenderer["contents"][0];
                if (const QJsonValue clarificationRenderer = sectionItem["clarificationRenderer"];
                    clarificationRenderer.isObject())
                {
                    clarification.emplace(clarificationRenderer);
                }
                else if (const QJsonValue commentsEntryPointHeaderRenderer = sectionItem["commentsEntryPointHeaderRenderer"];
                         commentsEntryPointHeaderRenderer.isObject())
                {
                    commentsEntryPointHeader.emplace(commentsEntryPointHeaderRenderer);
                }
                else if (const QJsonValue continuationItemRenderer = sectionItem["continuationItemRenderer"];
                         continuationItemRenderer.isObject())
                {
                    commentsSectionContinuation = continuationItemRenderer["continuationEndpoint"]["continuationCommand"]["token"].toString();
                }
                else if (const QJsonValue videoMetadataCarouselViewModel = sectionItem["videoMetadataCarouselViewModel"];
                         videoMetadataCarouselViewModel.isObject())
                {
                    videoMetadataCarousel.emplace(videoMetadataCarouselViewModel);
                }
            }
            else if (const QJsonValue videoPrimaryInfoRenderer = result["videoPrimaryInfoRenderer"];
                     videoPrimaryInfoRenderer.isObject())
            {
                primaryInfo = VideoPrimaryInfo(videoPrimaryInfoRenderer);
            }
            else if (const QJsonValue videoSecondaryInfoRenderer = result["videoSecondaryInfoRenderer"];
                     videoSecondaryInfoRenderer.isObject())
            {
                secondaryInfo = VideoSecondaryInfo(videoSecondaryInfoRenderer);
            }
        }
    }
}
