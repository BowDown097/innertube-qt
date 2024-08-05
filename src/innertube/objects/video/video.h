#pragma once
#include "innertube/objects/images/imagewithcolorpalette.h"
#include "innertube/objects/items/menu/menu.h"
#include "videoowner.h"
#include <QTime>

namespace InnertubeObjects
{
    struct Video
    {
        QList<MetadataBadge> badges;
        InnertubeString descriptionSnippet;
        QJsonValue inlinePlaybackEndpoint;
        InnertubeString lengthText;
        InnertubeString longBylineText;
        Menu menu;
        QJsonValue navigationEndpoint;
        VideoOwner owner;
        InnertubeString publishedTimeText;
        QString searchVideoResultEntityKey;
        InnertubeString shortBylineText;
        InnertubeString shortViewCountText;
        bool showActionMenu;
        ImageWithColorPalette thumbnail;
        InnertubeString title;
        QString videoId;
        InnertubeString viewCountText;

        explicit Video(const QJsonValue& videoRenderer);
        bool isLive() const;
        bool isReel() const;
        QTime length() const;
    };
}
