#pragma once
#include "innertube/objects/player/captiontrack.h"
#include "innertube/objects/player/playbacktracking.h"
#include "innertube/objects/player/playervideodetails.h"
#include "innertube/objects/player/streamingdata.h"

namespace InnertubeEndpoints
{
    struct PlayerResponse
    {
        QList<InnertubeObjects::CaptionTrack> captions;
        InnertubeObjects::PlaybackTracking playbackTracking;
        InnertubeObjects::StreamingData streamingData;
        InnertubeObjects::PlayerVideoDetails videoDetails;
    };
}
