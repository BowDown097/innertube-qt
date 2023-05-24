#include "notification.h"

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
        QJsonValue command = !notificationRenderer["navigationEndpoint"]["getCommentsFromInboxCommand"].isUndefined()
                                 ? notificationRenderer["navigationEndpoint"]["getCommentsFromInboxCommand"]
                                 : notificationRenderer["navigationEndpoint"]["watchEndpoint"];
        linkedCommentId = std::make_optional<QString>(command["linkedCommentId"].toString());
        videoId = command["videoId"].toString();
    }
}
