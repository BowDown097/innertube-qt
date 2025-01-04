#pragma once
#include "basevideo.h"
#include "innertube/objects/ad/adactiveview.h"
#include "innertube/objects/channel/metadatabadge.h"
#include "innertube/objects/items/button.h"

namespace InnertubeObjects
{
    struct VideoDisplayButtonGroup : BaseVideo
    {
        AdActiveView activeView;
        Button adCtaButton;
        MetadataBadge badge;
        QJsonValue channelEndpoint;
        ResponsiveImage channelThumbnail;
        InnertubeString description;
        QJsonValue inlinePlaybackEndpoint;
        QJsonValue onImpression;
        Button watchButton;

        VideoDisplayButtonGroup() = default;
        explicit VideoDisplayButtonGroup(const QJsonValue& videoDisplayButtonGroupRenderer)
            : BaseVideo(videoDisplayButtonGroupRenderer),
              activeView(videoDisplayButtonGroupRenderer["activeView"]),
              adCtaButton(videoDisplayButtonGroupRenderer["adCtaButton"]["buttonRenderer"]),
              badge(videoDisplayButtonGroupRenderer["badge"]["metadataBadgeRenderer"]),
              channelEndpoint(videoDisplayButtonGroupRenderer["channelEndpoint"]),
              channelThumbnail(videoDisplayButtonGroupRenderer["channelThumbnail"]["thumbnails"]),
              description(videoDisplayButtonGroupRenderer["description"]),
              inlinePlaybackEndpoint(videoDisplayButtonGroupRenderer["inlinePlaybackEndpoint"]),
              onImpression(videoDisplayButtonGroupRenderer["onImpression"]),
              watchButton(videoDisplayButtonGroupRenderer["watchButton"]["buttonRenderer"]) {}
    };
}
