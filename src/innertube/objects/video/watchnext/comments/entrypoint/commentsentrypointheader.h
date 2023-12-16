#ifndef COMMENTSENTRYPOINTHEADER_H
#define COMMENTSENTRYPOINTHEADER_H
#include "commentsentrypointteaser.h"
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    struct CommentsEntryPointHeader
    {
        QString commentCount;
        InnertubeString headerText;
        QJsonValue onTap;
        QString targetId;
        CommentsEntryPointTeaser teaser;

        CommentsEntryPointHeader() = default;
        explicit CommentsEntryPointHeader(const QJsonValue& commentsEntryPointHeaderRenderer)
            : commentCount(commentsEntryPointHeaderRenderer["commentCount"]["simpleText"].toString()),
              headerText(commentsEntryPointHeaderRenderer["headerText"]),
              onTap(commentsEntryPointHeaderRenderer["onTap"]),
              targetId(commentsEntryPointHeaderRenderer["targetId"].toString()),
              teaser(commentsEntryPointHeaderRenderer["contentRenderer"]["commentsEntryPointTeaserRenderer"]) {}
    };
}

#endif // COMMENTSENTRYPOINTHEADER_H
