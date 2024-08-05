#include "notification.h"

namespace InnertubeObjects
{
    Notification::Notification(const QJsonValue& notificationRenderer)
        : channelIcon(notificationRenderer["thumbnail"]["thumbnails"]),
          navigationEndpoint(notificationRenderer["navigationEndpoint"]),
          notificationId(notificationRenderer["notificationId"].toString()),
          read(notificationRenderer["read"].toBool()),
          shortMessage(notificationRenderer["shortMessage"]["simpleText"].toString()),
          sentTimeText(notificationRenderer["sentTimeText"]["simpleText"].toString()),
          videoThumbnail(notificationRenderer["videoThumbnail"]["thumbnails"])
    {
        const QJsonValue command = navigationEndpoint["getCommentsFromInboxCommand"].isObject()
            ? navigationEndpoint["getCommentsFromInboxCommand"] : navigationEndpoint["watchEndpoint"];
        linkedCommentId = command["linkedCommentId"].toString();
        videoId = command["videoId"].toString();
    }
}
