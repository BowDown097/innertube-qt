#ifndef VIDEOSECONDARYINFO_H
#define VIDEOSECONDARYINFO_H
#include "metadatarowcontainer.h"
#include "secondaryinfoowner.h"
#include "innertube/objects/channel/subscribebutton.h"

namespace InnertubeObjects
{
    class VideoSecondaryInfo
    {
    public:
        bool defaultExpanded;
        InnertubeString description;
        int descriptionCollapsedLines;
        MetadataRowContainer metadataRowContainer;
        SecondaryInfoOwner owner;
        QString showLessText;
        QString showMoreText;
        SubscribeButton subscribeButton;

        VideoSecondaryInfo() {}
        explicit VideoSecondaryInfo(const QJsonValue& secondaryInfoRenderer)
            : defaultExpanded(secondaryInfoRenderer["defaultExpanded"].toBool()),
              description(secondaryInfoRenderer["description"]),
              descriptionCollapsedLines(secondaryInfoRenderer["descriptionCollapsedLines"].toInt()),
              metadataRowContainer(secondaryInfoRenderer["metadataRowContainer"]["metadataRowContainerRenderer"]),
              owner(secondaryInfoRenderer["owner"]["videoOwnerRenderer"]),
              showLessText(secondaryInfoRenderer["showLessText"]["simpleText"].toString()),
              showMoreText(secondaryInfoRenderer["showMoreText"]["simpleText"].toString()),
              subscribeButton(secondaryInfoRenderer["subscribeButton"]["subscribeButtonRenderer"]) {}
    };
}

#endif // VIDEOSECONDARYINFO_H
