#ifndef COMMENTACTIONBUTTONS_H
#define COMMENTACTIONBUTTONS_H
#include "innertube/objects/items/button.h"
#include "innertube/objects/items/togglebutton.h"

namespace InnertubeObjects
{
    struct CommentActionButtons
    {
        ToggleButton dislikeButton;
        ToggleButton likeButton;
        Button replyButton;
        Button shareButton;
        QString style;

        explicit CommentActionButtons(const QJsonValue& commentActionButtonsRenderer)
            : dislikeButton(commentActionButtonsRenderer["dislikeButton"]["toggleButtonRenderer"]),
              likeButton(commentActionButtonsRenderer["likeButton"]["toggleButtonRenderer"]),
              replyButton(commentActionButtonsRenderer["replyButton"]["buttonRenderer"]),
              shareButton(commentActionButtonsRenderer["shareButton"]["buttonRenderer"]),
              style(commentActionButtonsRenderer["style"].toString()) {}
    };
}

#endif // COMMENTACTIONBUTTONS_H
