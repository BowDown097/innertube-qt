#include "commentreplies.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    CommentReplies::CommentReplies(const QJsonValue& commentRepliesRenderer)
        : hideReplies(commentRepliesRenderer["hideReplies"]["buttonRenderer"]),
          targetId(commentRepliesRenderer["targetId"].toString()),
          viewReplies(commentRepliesRenderer["viewReplies"]["buttonRenderer"])
    {
        const QJsonArray contents = commentRepliesRenderer["contents"].toArray();
        for (const QJsonValue& item : contents)
            if (const QJsonValue continuationItem = item["continuationItemRenderer"]; continuationItem.isObject())
                continuationToken = continuationItem["continuationEndpoint"]["continuationCommand"]["token"].toString();
    }
}
