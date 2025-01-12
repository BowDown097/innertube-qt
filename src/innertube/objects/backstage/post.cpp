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
        if (const QJsonValue image = backstageAttachmentJson["backstageImageRenderer"]; image.isObject())
            backstageAttachment = BackstageImage(image);
        else if (const QJsonValue poll = backstageAttachmentJson["pollRenderer"]; poll.isObject())
            backstageAttachment = Poll(poll);
        else if (const QJsonValue quiz = backstageAttachmentJson["quizRenderer"]; quiz.isObject())
            backstageAttachment = Quiz(quiz);
        else if (const QJsonValue video = backstageAttachmentJson["videoRenderer"]; video.isObject())
            backstageAttachment = Video(video);

        if (const QJsonValue voteButtonJson = postRenderer["voteButton"]; voteButtonJson.isObject())
            voteButton = Button(voteButtonJson["buttonRenderer"]);
    }
}
