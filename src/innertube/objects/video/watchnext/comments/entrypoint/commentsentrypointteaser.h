#ifndef COMMENTSENTRYPOINTTEASER_H
#define COMMENTSENTRYPOINTTEASER_H
#include "innertube/objects/imagewithaccessibility.h"
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    struct CommentsEntryPointTeaser
    {
        ImageWithAccessibility teaserAvatar;
        InnertubeString teaserContent;

        CommentsEntryPointTeaser() = default;
        explicit CommentsEntryPointTeaser(const QJsonValue& commentsEntryPointTeaserRenderer)
            : teaserAvatar(commentsEntryPointTeaserRenderer["teaserAvatar"]),
              teaserContent(commentsEntryPointTeaserRenderer["teaserContent"]) {}
    };
}

#endif // COMMENTSENTRYPOINTTEASER_H
