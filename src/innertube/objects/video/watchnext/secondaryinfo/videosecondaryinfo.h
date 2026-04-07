#pragma once
#include "innertube/objects/dynamictext.h"
#include "innertube/objects/channel/subscribebutton.h"
#include "innertube/objects/viewmodels/subscribebuttonviewmodel.h"
#include "metadatarowcontainer.h"
#include "videoowner.h"

namespace InnertubeObjects
{
    struct HeaderRun
    {
        QString headerMapping;
        int length{};
        int startIndex{};

        HeaderRun() = default;
        explicit HeaderRun(const QJsonValue& headerRun)
            : headerMapping(headerRun["headerMapping"].toString()),
              length(headerRun["length"].toInt()),
              startIndex(headerRun["startIndex"].toInt()) {}
    };

    struct VideoSecondaryInfo
    {
        DynamicText attributedDescription;
        bool defaultExpanded{};
        int descriptionCollapsedLines{};
        QList<HeaderRun> headerRuns;
        MetadataRowContainer metadataRowContainer;
        VideoOwner owner;
        QJsonValue showLessCommand;
        QString showLessText;
        QJsonValue showMoreCommand;
        QString showMoreText;
        std::variant<SubscribeButton, SubscribeButtonViewModel> subscribeButton;

        VideoSecondaryInfo() = default;
        explicit VideoSecondaryInfo(const QJsonValue& secondaryInfoRenderer);
    };
}
