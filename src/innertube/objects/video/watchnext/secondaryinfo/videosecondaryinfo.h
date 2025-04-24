#pragma once
#include "metadatarowcontainer.h"
#include "videoowner.h"
#include "innertube/objects/dynamictext.h"
#include "innertube/objects/channel/subscribebutton.h"

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
        SubscribeButton subscribeButton;

        VideoSecondaryInfo() = default;
        explicit VideoSecondaryInfo(const QJsonValue& secondaryInfoRenderer);
    };
}
