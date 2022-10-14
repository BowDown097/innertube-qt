#ifndef PLAYER_H
#define PLAYER_H
#include "../base/baseendpoint.h"
#include "innertube/objects/player/captiontrack.h"
#include "innertube/objects/player/playbacktracking.h"
#include "innertube/objects/player/playervideodetails.h"
#include "innertube/objects/player/streamingdata.h"

namespace InnertubeEndpoints
{
    class Player : public BaseEndpoint
    {
        friend class ::InnerTube;
    public:
        QList<InnertubeObjects::CaptionTrack> captions;
        InnertubeObjects::PlaybackTracking playbackTracking;
        InnertubeObjects::StreamingData streamingData;
        InnertubeObjects::PlayerVideoDetails videoDetails;
    private:
        Player(const QString& videoId, InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore);
    };
}


#endif // PLAYER_H
