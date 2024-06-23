#pragma once
#include "innertube/objects/innertubestring.h"
#include "innertube/objects/responsiveimage.h"
#include "videoowner.h"
#include <QTime>

namespace InnertubeObjects
{
    struct Video
    {
        InnertubeString descriptionSnippet;
        bool isLive;
        InnertubeString lengthText;
        InnertubeString longBylineText;
        QJsonValue navigationEndpoint;
        VideoOwner owner;
        InnertubeString publishedTimeText;
        InnertubeString shelf;
        InnertubeString shortBylineText;
        InnertubeString shortViewCountText;
        bool showActionMenu;
        ResponsiveImage thumbnail;
        InnertubeString title;
        QString videoId;
        InnertubeString viewCountText;

        explicit Video(const QJsonValue& videoRenderer, const InnertubeString& shelf = InnertubeString());
        bool isReel() const;
        QTime length() const;
    };
}
