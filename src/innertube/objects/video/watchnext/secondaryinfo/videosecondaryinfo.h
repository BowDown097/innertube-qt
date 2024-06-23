#pragma once
#include "metadatarowcontainer.h"
#include "secondaryinfoowner.h"
#include "innertube/objects/dynamictext.h"
#include "innertube/objects/channel/subscribebutton.h"

namespace InnertubeObjects
{
    struct VideoSecondaryInfo
    {
        DynamicText attributedDescription;
        bool defaultExpanded{};
        int descriptionCollapsedLines{};
        MetadataRowContainer metadataRowContainer;
        SecondaryInfoOwner owner;
        QString showLessText;
        QString showMoreText;
        SubscribeButton subscribeButton;

        VideoSecondaryInfo() = default;
        explicit VideoSecondaryInfo(const QJsonValue& secondaryInfoRenderer)
            : attributedDescription(secondaryInfoRenderer["attributedDescription"]),
              defaultExpanded(secondaryInfoRenderer["defaultExpanded"].toBool()),
              descriptionCollapsedLines(secondaryInfoRenderer["descriptionCollapsedLines"].toInt()),
              metadataRowContainer(secondaryInfoRenderer["metadataRowContainer"]["metadataRowContainerRenderer"]),
              owner(secondaryInfoRenderer["owner"]["videoOwnerRenderer"]),
              showLessText(secondaryInfoRenderer["showLessText"]["simpleText"].toString()),
              showMoreText(secondaryInfoRenderer["showMoreText"]["simpleText"].toString()),
              subscribeButton(secondaryInfoRenderer["subscribeButton"]["subscribeButtonRenderer"]) {}
    };
}
