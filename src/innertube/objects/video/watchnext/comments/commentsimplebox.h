#pragma once
#include "innertube/objects/images/imagewithaccessibility.h"
#include "innertube/objects/innertubestring.h"
#include "innertube/objects/items/button.h"
#include "innertube/objects/items/emoji/picker/emojipicker.h"

namespace InnertubeObjects
{
    struct CommentSimplebox
    {
        ImageWithAccessibility authorThumbnail;
        QString avatarSize;
        Button emojiButton;
        EmojiPicker emojiPicker;
        InnertubeString placeholderText;
        QJsonValue prepareAccountEndpoint;

        CommentSimplebox() = default;
        explicit CommentSimplebox(const QJsonValue& commentSimpleboxRenderer)
            : authorThumbnail(commentSimpleboxRenderer["authorThumbnail"]),
              avatarSize(commentSimpleboxRenderer["avatarSize"].toString()),
              emojiButton(commentSimpleboxRenderer["emojiButton"]["buttonRenderer"]),
              emojiPicker(commentSimpleboxRenderer["emojiPicker"]["emojiPickerRenderer"]),
              placeholderText(commentSimpleboxRenderer["placeholderText"]),
              prepareAccountEndpoint(commentSimpleboxRenderer["prepareAccountEndpoint"]) {}
    };
}
