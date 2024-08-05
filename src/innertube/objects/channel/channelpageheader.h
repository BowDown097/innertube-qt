#pragma once
#include "innertube/objects/images/responsiveimage.h"
#include "innertube/objects/viewmodels/buttonviewmodel.h"
#include "innertube/objects/viewmodels/contentmetadataviewmodel.h"
#include "innertube/objects/viewmodels/dynamictextviewmodel.h"
#include "innertube/objects/viewmodels/subscribebuttonviewmodel.h"

namespace InnertubeObjects
{
    struct ChannelPageHeader
    {
        QList<ButtonViewModel> actions; // subscribeButton is also an action, but is separate for simplicity
        DynamicTextViewModel attribution;
        ResponsiveImage avatar;
        ResponsiveImage banner;
        DynamicTextViewModel description;
        ContentMetadataViewModel metadata;
        std::optional<SubscribeButtonViewModel> subscribeButton;
        DynamicTextViewModel title;

        ChannelPageHeader() = default;
        explicit ChannelPageHeader(const QJsonValue& pageHeaderViewModel);
    };
}
