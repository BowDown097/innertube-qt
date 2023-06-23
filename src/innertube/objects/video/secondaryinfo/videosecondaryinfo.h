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
        bool defaultExpanded = false;
        InnertubeString description;
        int descriptionCollapsedLines = 0;
        MetadataRowContainer metadataRowContainer;
        SecondaryInfoOwner owner;
        QString showLessText;
        QString showMoreText;
        SubscribeButton subscribeButton;

        VideoSecondaryInfo() = default;
        explicit VideoSecondaryInfo(const QJsonValue& secondaryInfoRenderer);
    };
}

#endif // VIDEOSECONDARYINFO_H
