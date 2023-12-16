#include "backstagepost.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    BackstagePost::BackstagePost(const QJsonValue& backstagePostRenderer)
        : actionButtons(backstagePostRenderer["actionButtons"]["commentActionButtonsRenderer"]),
          actionMenu(backstagePostRenderer["actionMenu"]["menuRenderer"]),
          authorEndpoint(backstagePostRenderer["authorEndpoint"]),
          authorText(backstagePostRenderer["authorText"]),
          authorThumbnail(backstagePostRenderer["authorThumbnail"]["thumbnails"]),
          collapseButton(backstagePostRenderer["collapseButton"]["buttonRenderer"]),
          contentText(backstagePostRenderer["contentText"]),
          expandButton(backstagePostRenderer["expandButton"]["buttonRenderer"]),
          pollStatus(backstagePostRenderer["pollStatus"].toString()),
          postId(backstagePostRenderer["postId"].toString()),
          publishedTimeText(backstagePostRenderer["publishedTimeText"]),
          surface(backstagePostRenderer["surface"].toString()),
          voteCount(backstagePostRenderer["voteCount"]),
          voteStatus(backstagePostRenderer["voteStatus"].toString())
    {
        const QJsonValue backstageAttachmentJson = backstagePostRenderer["backstageAttachment"];
        if (backstageAttachmentJson["pollRenderer"].isObject())
            backstageAttachment = Poll(backstageAttachmentJson["pollRenderer"]);
        else if (backstageAttachmentJson["backstageImageRenderer"].isObject())
            backstageAttachment = BackstageImage(backstageAttachmentJson["backstageImageRenderer"]);
        else if (backstageAttachmentJson["videoRenderer"].isObject())
            backstageAttachment = Video(backstageAttachmentJson["videoRenderer"]);
    }
}
