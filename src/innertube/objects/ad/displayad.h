#pragma once
#include "adactiveview.h"
#include "innertube/objects/channel/metadatabadge.h"
#include "innertube/objects/images/responsiveimage.h"
#include "innertube/objects/innertubestring.h"
#include "innertube/objects/items/button.h"
#include "innertube/objects/items/menu/menu.h"

namespace InnertubeObjects
{
    struct DisplayAd
    {
        AdActiveView activeView;
        MetadataBadge badge;
        InnertubeString bodyText;
        QJsonValue clickCommand;
        Button ctaButton;
        ResponsiveImage image;
        QJsonArray impressionEndpoints;
        QString layout;
        MetadataBadge mediaBadge;
        Button mediaHoverOverlay;
        Menu menu;
        InnertubeString secondaryText;
        InnertubeString titleText;

        DisplayAd() = default;
        explicit DisplayAd(const QJsonValue& displayAdRenderer)
            : activeView(displayAdRenderer["activeView"]),
              badge(displayAdRenderer["badge"]["metadataBadgeRenderer"]),
              bodyText(displayAdRenderer["bodyText"]),
              clickCommand(displayAdRenderer["clickCommand"]),
              ctaButton(displayAdRenderer["ctaButton"]["buttonRenderer"]),
              image(displayAdRenderer["image"]["thumbnail"]["thumbnails"]),
              impressionEndpoints(displayAdRenderer["impressionEndpoints"].toArray()),
              layout(displayAdRenderer["layout"].toString()),
              mediaBadge(displayAdRenderer["mediaBadge"]["metadataBadgeRenderer"]),
              mediaHoverOverlay(displayAdRenderer["mediaOverlay"]["buttonRenderer"]),
              menu(displayAdRenderer["menu"]["menuRenderer"]),
              secondaryText(displayAdRenderer["secondaryText"]),
              titleText(displayAdRenderer["titleText"]) {}
    };
}
