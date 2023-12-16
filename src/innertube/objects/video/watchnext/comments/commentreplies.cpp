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
        {
            if (item["continuationItemRenderer"].isObject())
            {
                continuationToken = item["continuationItemRenderer"]["continuationEndpoint"]
                                        ["continuationCommand"]["token"].toString();
            }
        }
    }
}
