#include "videosecondaryinfo.h"
#include <QJsonArray>
#include <QJsonObject>

namespace InnertubeObjects
{
    VideoSecondaryInfo::VideoSecondaryInfo(const QJsonValue& secondaryInfoRenderer)
        : channelName(secondaryInfoRenderer["owner"]["videoOwnerRenderer"]["title"]),
          description(secondaryInfoRenderer["description"]),
          subscribeButton(secondaryInfoRenderer["subscribeButton"]["subscribeButtonRenderer"]),
          subscriberCountText(secondaryInfoRenderer["owner"]["videoOwnerRenderer"]["subscriberCountText"])
    {
        const QJsonArray thumbnails = secondaryInfoRenderer["owner"]["videoOwnerRenderer"]["thumbnail"]["thumbnails"].toArray();
        for (const QJsonValue& v : thumbnails)
            channelIcons.append(GenericThumbnail(v));
    }
}
