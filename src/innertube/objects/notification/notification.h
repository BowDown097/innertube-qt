#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include "innertube/objects/genericthumbnail.h"
#include <QPair>

namespace InnertubeObjects
{
    class Notification
    {
    public:
        GenericThumbnail channelIcon;
        QPair<QString, bool> linkedCommentId;
        long long notificationId;
        bool read;
        QString shortMessage;
        QString sentTimeText;
        QString videoId;
        GenericThumbnail videoThumbnail;

        explicit Notification(const QJsonValue& notificationRenderer);
    };
}

#endif // NOTIFICATION_H
