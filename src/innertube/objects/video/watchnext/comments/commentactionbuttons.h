#pragma once
#include "innertube/objects/items/button.h"
#include "innertube/objects/items/togglebutton.h"

namespace InnertubeObjects
{
    struct CommentActionButtons
    {
        ToggleButton dislikeButton;
        ToggleButton likeButton;
        QString protoCreationMs;
        Button replyButton;
        Button shareButton;
        QString style;

        CommentActionButtons() = default;
        explicit CommentActionButtons(const QJsonValue& commentActionButtonsRenderer)
            : dislikeButton(commentActionButtonsRenderer["dislikeButton"]["toggleButtonRenderer"]),
              likeButton(commentActionButtonsRenderer["likeButton"]["toggleButtonRenderer"]),
              protoCreationMs(commentActionButtonsRenderer["protoCreationMs"].toString()),
              replyButton(commentActionButtonsRenderer["replyButton"]["buttonRenderer"]),
              shareButton(commentActionButtonsRenderer["shareButton"]["buttonRenderer"]),
              style(commentActionButtonsRenderer["style"].toString()) {}
    };
}
