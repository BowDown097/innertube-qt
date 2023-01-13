#include "videoprimaryinfo.h"
#include "jsonutil.h"
#include <QJsonArray>
#include <QJsonObject>

namespace InnertubeObjects
{
    VideoPrimaryInfo::VideoPrimaryInfo(const QJsonValue& primaryInfoRenderer)
        : dateText(primaryInfoRenderer["dateText"]),
          relativeDateText(primaryInfoRenderer["relativeDateText"]),
          shortViewCount(primaryInfoRenderer["viewCount"]["videoViewCountRenderer"]["shortViewCount"]),
          title(primaryInfoRenderer["title"]), viewCount(primaryInfoRenderer["viewCount"]["videoViewCountRenderer"]["viewCount"])
    {
        // this is awful
        QJsonValue likeButton = JsonUtil::rfind("likeButton", primaryInfoRenderer["videoActions"]["menuRenderer"]["topLevelButtons"]);
        QString likeLabel = likeButton["toggleButtonRenderer"]["defaultText"]["accessibility"]["accessibilityData"]["label"].toString();
        if (likeLabel.isEmpty())
            return;

        QString countStr;
        QRegularExpressionMatchIterator i = numberRegex.globalMatch(likeLabel);
        while (i.hasNext())
        {
            QRegularExpressionMatch match = i.next();
            countStr += match.captured(0);
        }

        likeCount = countStr.toInt();
    }
}
