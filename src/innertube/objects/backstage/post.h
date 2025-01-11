#pragma once
#include "backstageimage.h"
#include "innertube/objects/images/responsiveimage.h"
#include "innertube/objects/items/menu/menu.h"
#include "innertube/objects/video/video.h"
#include "innertube/objects/video/watchnext/comments/commentactionbuttons.h"
#include "poll/poll.h"

namespace InnertubeObjects
{
    struct Post
    {
        // these are available in Post and BackstagePost
        CommentActionButtons actionButtons;
        Menu actionMenu;
        QJsonValue authorEndpoint;
        InnertubeString authorText;
        ResponsiveImage authorThumbnail;
        std::variant<std::monostate, BackstageImage, Poll, Video> backstageAttachment;
        InnertubeString contentText;
        QString pollStatus;
        QString postId;
        InnertubeString publishedTimeText;
        QString surface;
        InnertubeString voteCount;
        QString voteStatus;

        // this is only available in Post
        std::optional<Button> voteButton;

        explicit Post(const QJsonValue& postRenderer);
    };
}
