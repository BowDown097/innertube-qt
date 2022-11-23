#include "videoprimaryinfo.h"
#include <QJsonArray>
#include <QJsonObject>

namespace InnertubeObjects
{
    VideoPrimaryInfo::VideoPrimaryInfo(const QJsonValue& primaryInfoRenderer) : dateText(primaryInfoRenderer["dateText"]),
        relativeDateText(primaryInfoRenderer["relativeDateText"]),
        shortViewCount(primaryInfoRenderer["viewCount"]["videoViewCountRenderer"]["shortViewCount"]),
        title(primaryInfoRenderer["title"]), viewCount(primaryInfoRenderer["viewCount"]["videoViewCountRenderer"]["viewCount"]),
        primaryInfoRenderer(primaryInfoRenderer)
    {
        // this is awful
        QString likeLabel = retrieveTopLevelButton("watch-like")["toggleButtonRenderer"]["accessibility"]["label"].toString();
        QString countStr;
        QRegularExpressionMatchIterator i = numberRegex.globalMatch(likeLabel);
        while (i.hasNext())
        {
            QRegularExpressionMatch match = i.next();
            countStr += match.captured(0);
        }

        likeCount = countStr.toInt();
    }

    QJsonValue VideoPrimaryInfo::retrieveTopLevelButton(const QString& targetId)
    {
        QJsonArray topLevelButtons = primaryInfoRenderer["videoActions"]["menuRenderer"]["topLevelButtons"].toArray();
        if (topLevelButtons.isEmpty()) return QJsonValue();
        return *std::ranges::find_if(topLevelButtons, [&targetId](const QJsonValue& v) {
            return (*v.toObject().constBegin()).toObject()["targetId"].toString() == targetId;
        });
    }
}
