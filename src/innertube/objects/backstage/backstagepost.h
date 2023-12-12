#ifndef BACKSTAGEPOST_H
#define BACKSTAGEPOST_H
#include "backstageimage.h"
#include "commentactionbuttons.h"
#include "innertube/objects/items/menuserviceitem.h"
#include "innertube/objects/responsiveimage.h"
#include "innertube/objects/video/video.h"
#include "poll/poll.h"

namespace InnertubeObjects
{
    struct BackstagePost
    {
        CommentActionButtons actionButtons;
        QList<MenuServiceItem> actionMenu;
        QJsonValue authorEndpoint;
        InnertubeString authorText;
        ResponsiveImage authorThumbnail;
        std::variant<std::monostate, BackstageImage, Poll, Video> backstageAttachment;
        Button collapseButton;
        InnertubeString contentText;
        Button expandButton;
        std::optional<QString> pollStatus;
        QString postId;
        InnertubeString publishedTimeText;
        QString surface;
        InnertubeString voteCount;
        QString voteStatus;

        explicit BackstagePost(const QJsonValue& backstagePostRenderer);
    };
}

#endif // BACKSTAGEPOST_H
