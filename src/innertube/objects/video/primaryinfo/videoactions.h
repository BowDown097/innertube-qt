#ifndef VIDEOACTIONS_H
#define VIDEOACTIONS_H
#include "innertube/objects/togglebutton.h"
#include "jsonutil.h"

namespace InnertubeObjects
{
    class VideoActions
    {
    public:
        QString accessibilityLabel;
        ToggleButton dislikeButton;
        ToggleButton likeButton;

        VideoActions() {}
        explicit VideoActions(const QJsonValue& menuRenderer)
            : accessibilityLabel(menuRenderer["accessibility"]["accessibilityData"]["label"].toString()),
              dislikeButton(JsonUtil::rfind("dislikeButton", menuRenderer["topLevelButtons"])["toggleButtonRenderer"]),
              likeButton(JsonUtil::rfind("likeButton", menuRenderer["topLevelButtons"])["toggleButtonRenderer"]) {}
    };
}

#endif // VIDEOACTIONS_H
