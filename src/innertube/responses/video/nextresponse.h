#ifndef NEXTRESPONSE_H
#define NEXTRESPONSE_H
#include "innertube/objects/live_chat/livechat.h"
#include "innertube/objects/video/primaryinfo/videoprimaryinfo.h"
#include "innertube/objects/video/secondaryinfo/videosecondaryinfo.h"
#include <optional>

namespace InnertubeEndpoints
{
    struct NextResponse
    {
        std::optional<InnertubeObjects::LiveChat> liveChat;
        InnertubeObjects::VideoPrimaryInfo primaryInfo;
        InnertubeObjects::VideoSecondaryInfo secondaryInfo;
        QString videoId;
    };
}

#endif // NEXTRESPONSE_H
