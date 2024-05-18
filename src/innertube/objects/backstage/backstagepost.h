#pragma once
#include "backstageimage.h"
#include "innertube/objects/items/menu/menu.h"
#include "innertube/objects/responsiveimage.h"
#include "innertube/objects/video/video.h"
#include "innertube/objects/video/watchnext/comments/commentactionbuttons.h"
#include "poll/poll.h"

namespace InnertubeObjects
{
    struct BackstagePost
    {
        CommentActionButtons actionButtons;
        Menu actionMenu;
        QJsonValue authorEndpoint;
        InnertubeString authorText;
        ResponsiveImage authorThumbnail;
        std::variant<std::monostate, BackstageImage, Poll, Video> backstageAttachment;
        Button collapseButton;
        InnertubeString contentText;
        Button expandButton;
        QString pollStatus;
        QString postId;
        InnertubeString publishedTimeText;
        QString surface;
        InnertubeString voteCount;
        QString voteStatus;

        explicit BackstagePost(const QJsonValue& backstagePostRenderer);
    };
}
