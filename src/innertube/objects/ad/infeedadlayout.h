#pragma once
#include "adlayoutmetadata.h"
#include "displayad.h"
#include "innertube/objects/video/videodisplaybuttongroup.h"

namespace InnertubeObjects
{
    struct InFeedAdLayout
    {
        AdLayoutMetadata adLayoutMetadata;
        std::variant<DisplayAd, VideoDisplayButtonGroup> renderingContent;

        InFeedAdLayout() = default;
        explicit InFeedAdLayout(const QJsonValue& inFeedAdLayoutRenderer)
            : adLayoutMetadata(inFeedAdLayoutRenderer["adLayoutMetadata"])
        {
            const QJsonValue renderingContentJson = inFeedAdLayoutRenderer["renderingContent"];
            if (const QJsonValue displayAd = renderingContentJson["displayAdRenderer"]; displayAd.isObject())
                renderingContent = DisplayAd(displayAd);
            else if (const QJsonValue video = renderingContentJson["videoDisplayButtonGroupRenderer"]; video.isObject())
                renderingContent = VideoDisplayButtonGroup(video);
        }
    };
}
