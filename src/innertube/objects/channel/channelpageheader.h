#pragma once
#include "innertube/objects/viewmodels/buttonviewmodel.h"
#include "innertube/objects/viewmodels/contentmetadataviewmodel.h"
#include "innertube/objects/viewmodels/decoratedavatarviewmodel.h"
#include "innertube/objects/viewmodels/dynamictextviewmodel.h"
#include "innertube/objects/viewmodels/flexibleactionsviewmodel.h"
#include "innertube/objects/viewmodels/imagebannerviewmodel.h"
#include "innertube/objects/viewmodels/subscribebuttonviewmodel.h"

namespace InnertubeObjects
{
    struct ChannelPageHeader
    {
        FlexibleActionsViewModel<ButtonViewModel, SubscribeButtonViewModel> actions;
        DynamicTextViewModel attribution;
        ImageBannerViewModel banner;
        DynamicTextViewModel description;
        DecoratedAvatarViewModel image;
        ContentMetadataViewModel metadata;
        QJsonValue rendererContext;
        DynamicTextViewModel title;

        ChannelPageHeader() = default;
        explicit ChannelPageHeader(const QJsonValue& pageHeaderViewModel)
            : actions(pageHeaderViewModel["actions"]["flexibleActionsViewModel"],
                      { "buttonViewModel", "subscribeButtonViewModel" }),
              attribution(pageHeaderViewModel["attribution"]["attributionViewModel"]),
              banner(pageHeaderViewModel["banner"]["imageBannerViewModel"]),
              description(pageHeaderViewModel["description"]["descriptionPreviewViewModel"], "description"),
              image(pageHeaderViewModel["image"]["decoratedAvatarViewModel"]),
              metadata(pageHeaderViewModel["metadata"]["contentMetadataViewModel"]),
              rendererContext(pageHeaderViewModel["rendererContext"]),
              title(pageHeaderViewModel["title"]["dynamicTextViewModel"]) {}
    };
}
