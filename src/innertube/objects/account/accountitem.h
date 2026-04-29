#pragma once
#include "innertube/objects/images/responsiveimage.h"
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    struct AccountItem
    {
        InnertubeString accountByline;
        QList<int> accountLogDirectiveInts;
        InnertubeString accountName;
        ResponsiveImage accountPhoto;
        InnertubeString channelHandle;
        bool hasChannel{};
        bool isDisabled{};
        bool isSelected{};
        ResponsiveImage mobileBanner;
        QJsonValue serviceEndpoint;

        AccountItem() = default;
        explicit AccountItem(const QJsonValue& accountItemRenderer);

        QString channelOrPageId() const;
    };
}