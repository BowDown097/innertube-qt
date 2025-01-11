#include "post.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    Post::Post(const QJsonValue& postRenderer)
        : actionButtons(postRenderer["actionButtons"]["commentActionButtonsRenderer"]),
          actionMenu(postRenderer["actionMenu"]["menuRenderer"]),
          authorEndpoint(postRenderer["authorEndpoint"]),
          authorText(postRenderer["authorText"]),
          authorThumbnail(postRenderer["authorThumbnail"]["thumbnails"]),
          contentText(postRenderer["contentText"]),
          pollStatus(postRenderer["pollStatus"].toString()),
          postId(postRenderer["postId"].toString()),
          publishedTimeText(postRenderer["publishedTimeText"]),
          surface(postRenderer["surface"].toString()),
          voteCount(postRenderer["voteCount"]),
          voteStatus(postRenderer["voteStatus"].toString())
    {
        const QJsonValue backstageAttachmentJson = postRenderer["backstageAttachment"];
        if (backstageAttachmentJson["pollRenderer"].isObject())
            backstageAttachment = Poll(backstageAttachmentJson["pollRenderer"]);
        else if (backstageAttachmentJson["backstageImageRenderer"].isObject())
            backstageAttachment = BackstageImage(backstageAttachmentJson["backstageImageRenderer"]);
        else if (backstageAttachmentJson["videoRenderer"].isObject())
            backstageAttachment = Video(backstageAttachmentJson["videoRenderer"]);

        if (const QJsonValue voteButtonJson = postRenderer["voteButton"]; voteButtonJson.isObject())
            voteButton = Button(voteButtonJson["buttonRenderer"]);
    }
}
