#pragma once
#include "innertube/objects/viewmodels/lockupviewmodel.h"
#include "innertube/objects/video/video.h"

namespace InnertubeEndpoints
{
    struct HistoryResponse
    {
        QList<std::variant<InnertubeObjects::Video, InnertubeObjects::LockupViewModel>> videos;
    };
}
