#ifndef COMMENT_H
#define COMMENT_H
#include "authorcommentbadge.h"
#include "commentactionbuttons.h"
#include "innertube/objects/imagewithaccessibility.h"
#include "innertube/objects/items/menu/menu.h"
#include "pinnedcommentbadge.h"

namespace InnertubeObjects
{
    struct Comment
    {
        CommentActionButtons actionButtons;
        Menu actionMenu;
        std::optional<AuthorCommentBadge> authorCommentBadge;
        QJsonValue authorEndpoint;
        bool authorIsChannelOwner;
        QString authorText;
        ImageWithAccessibility authorThumbnail;
        Button collapseButton;
        QString commentId;
        InnertubeString contentText;
        ResponsiveImage currentUserReplyThumbnail;
        Button expandButton;
        bool isLiked;
        std::optional<PinnedCommentBadge> pinnedCommentBadge;
        InnertubeString publishedTimeText;
        int replyCount;
        InnertubeString voteCount;
        QString voteStatus;

        Comment() = default;
        explicit Comment(const QJsonValue& commentRenderer)
            : actionButtons(commentRenderer["actionButtons"]["commentActionButtonsRenderer"]),
              actionMenu(commentRenderer["actionMenu"]["menuRenderer"]),
              authorCommentBadge(commentRenderer["authorCommentBadge"].isObject()
                                 ? std::make_optional<AuthorCommentBadge>(commentRenderer["authorCommentBadge"]["authorCommentBadgeRenderer"])
                                 : std::nullopt),
              authorEndpoint(commentRenderer["authorEndpoint"]),
              authorIsChannelOwner(commentRenderer["authorIsChannelOwner"].toBool()),
              authorText(commentRenderer["authorText"]["simpleText"].toString()),
              authorThumbnail(commentRenderer["authorThumbnail"]),
              collapseButton(commentRenderer["collapseButton"]["buttonRenderer"]),
              commentId(commentRenderer["commentId"].toString()),
              contentText(commentRenderer["contentText"]),
              currentUserReplyThumbnail(commentRenderer["currentUserReplyThumbnail"]["thumbnails"]),
              expandButton(commentRenderer["expandButton"]["buttonRenderer"]),
              isLiked(commentRenderer["isLiked"].toBool()),
              pinnedCommentBadge(commentRenderer["pinnedCommentBadge"].isObject()
                                 ? std::make_optional<PinnedCommentBadge>(commentRenderer["pinnedCommentBadge"]["pinnedCommentBadgeRenderer"])
                                 : std::nullopt),
              publishedTimeText(commentRenderer["publishedTimeText"]),
              replyCount(commentRenderer["replyCount"].toInt()),
              voteCount(commentRenderer["voteCount"]),
              voteStatus(commentRenderer["voteStatus"].toString()) {}
    };
}

#endif // COMMENT_H
