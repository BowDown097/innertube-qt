#ifndef CHANNELHEADER_H
#define CHANNELHEADER_H
#include "innertube/objects/responsiveimage.h"
#include "innertube/objects/viewmodels/buttonviewmodel.h"
#include "innertube/objects/viewmodels/contentmetadataviewmodel.h"
#include "innertube/objects/viewmodels/dynamictextviewmodel.h"
#include "innertube/objects/viewmodels/subscribebuttonviewmodel.h"

namespace InnertubeObjects
{
    struct ChannelHeader
    {
        QList<ButtonViewModel> actions; // subscribeButton is also an action, but is separate for simplicity
        DynamicTextViewModel attribution;
        ResponsiveImage avatar;
        ResponsiveImage banner;
        DynamicTextViewModel description;
        ContentMetadataViewModel metadata;
        std::optional<SubscribeButtonViewModel> subscribeButton;
        DynamicTextViewModel title;

        ChannelHeader() = default;
        explicit ChannelHeader(const QJsonValue& pageHeaderViewModel);
    };
}

#endif // CHANNELHEADER_H
