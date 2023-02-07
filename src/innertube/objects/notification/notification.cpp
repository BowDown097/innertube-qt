#include "notification.h"
#include <QJsonObject>

namespace InnertubeObjects
{
    Notification::Notification(const QJsonValue& notificationRenderer)
        : channelIcon(notificationRenderer["thumbnail"]["thumbnails"][0]),
          notificationId(notificationRenderer["notificationId"].toString().toLongLong()),
          read(notificationRenderer["read"].toBool()),
          shortMessage(notificationRenderer["shortMessage"]["simpleText"].toString()),
          sentTimeText(notificationRenderer["sentTimeText"]["simpleText"].toString()),
          videoThumbnail(notificationRenderer["videoThumbnail"]["thumbnails"][0])
    {
        const QJsonObject navigationEndpoint = notificationRenderer["navigationEndpoint"].toObject();
        bool hasCommentsCommand = navigationEndpoint.contains("getCommentsFromInboxCommand");
        QJsonValue command = hasCommentsCommand
                ? navigationEndpoint["getCommentsFromInboxCommand"]
                : navigationEndpoint["watchEndpoint"];

        linkedCommentId = std::make_optional<QString>(command["linkedCommentId"].toString());
        videoId = command["videoId"].toString();
    }
}
