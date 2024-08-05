#pragma once
#include "innertube/objects/images/responsiveimage.h"

namespace InnertubeObjects
{
    struct Notification
    {
        ResponsiveImage channelIcon;
        QString linkedCommentId;
        QJsonValue navigationEndpoint;
        QString notificationId;
        bool read;
        QString shortMessage;
        QString sentTimeText;
        QString videoId;
        ResponsiveImage videoThumbnail;

        explicit Notification(const QJsonValue& notificationRenderer);
    };
}
