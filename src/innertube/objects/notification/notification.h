#pragma once
#include "innertube/objects/images/genericthumbnail.h"
#include <optional>

namespace InnertubeObjects
{
    struct Notification
    {
        GenericThumbnail channelIcon;
        std::optional<QString> linkedCommentId;
        QString notificationId;
        bool read;
        QString shortMessage;
        QString sentTimeText;
        QString videoId;
        GenericThumbnail videoThumbnail;

        explicit Notification(const QJsonValue& notificationRenderer);
    };
}
