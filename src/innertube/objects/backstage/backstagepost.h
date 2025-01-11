#pragma once
#include "post.h"

namespace InnertubeObjects
{
    struct BackstagePost : Post
    {
        Button collapseButton;
        Button expandButton;

        explicit BackstagePost(const QJsonValue& backstagePostRenderer)
            : Post(backstagePostRenderer),
              collapseButton(backstagePostRenderer["collapseButton"]["buttonRenderer"]),
              expandButton(backstagePostRenderer["expandButton"]["buttonRenderer"]) {}
    };
}
