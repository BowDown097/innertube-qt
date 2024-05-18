#pragma once
#include "commentsimplebox.h"
#include "innertube/objects/items/emoji/emoji.h"
#include "innertube/objects/items/sortfiltersubmenu.h"

namespace InnertubeObjects
{
    struct CommentsHeader
    {
        CommentSimplebox commentSimplebox;
        InnertubeString commentsCount;
        InnertubeString countText;
        QList<Emoji> customEmojis;
        bool showSeparator;
        SortFilterSubMenu sortMenu;
        InnertubeString titleText;
        QString unicodeEmojisUrl;

        CommentsHeader() = default;
        explicit CommentsHeader(const QJsonValue& commentsHeaderRenderer);
    };
}
