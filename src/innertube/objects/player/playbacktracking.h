#ifndef PLAYBACKTRACKING_H
#define PLAYBACKTRACKING_H

namespace InnertubeObjects
{
    class PlaybackTracking
    {
    public:
        QString atrUrl, ptrackingUrl, qoeUrl, videostatsDelayplayUrl, videostatsPlaybackUrl, videostatsWatchtimeUrl;
        PlaybackTracking() {}
        explicit PlaybackTracking(const QJsonValue& playbackTracking) : atrUrl(playbackTracking["atrUrl"]["baseUrl"].toString()),
            ptrackingUrl(playbackTracking["ptrackingUrl"]["baseUrl"].toString()), qoeUrl(playbackTracking["qoeUrl"]["baseUrl"].toString()),
            videostatsDelayplayUrl(playbackTracking["videostatsDelayplayUrl"]["baseUrl"].toString()),
            videostatsPlaybackUrl(playbackTracking["videostatsPlaybackUrl"]["baseUrl"].toString()),
            videostatsWatchtimeUrl(playbackTracking["videostatsWatchtimeUrl"]["baseUrl"].toString()) {}
    };
}

#endif // PLAYBACKTRACKING_H
