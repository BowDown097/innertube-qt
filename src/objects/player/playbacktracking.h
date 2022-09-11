#ifndef PLAYBACKTRACKING_H
#define PLAYBACKTRACKING_H

namespace InnertubeObjects
{
    class PlaybackTracking
    {
    public:
        QString atrUrl, ptrackingUrl, qoeUrl, videostatsDelayplayUrl, videostatsPlaybackUrl, videostatsWatchtimeUrl;
        PlaybackTracking() {}
        PlaybackTracking(const QJsonObject& playbackTracking)
        {
            atrUrl = playbackTracking["atrUrl"].toObject()["baseUrl"].toString();
            ptrackingUrl = playbackTracking["ptrackingUrl"].toObject()["baseUrl"].toString();
            qoeUrl = playbackTracking["qoeUrl"].toObject()["baseUrl"].toString();
            videostatsDelayplayUrl = playbackTracking["videostatsDelayplayUrl"].toObject()["baseUrl"].toString();
            videostatsPlaybackUrl = playbackTracking["videostatsPlaybackUrl"].toObject()["baseUrl"].toString();
            videostatsWatchtimeUrl = playbackTracking["videostatsWatchtimeUrl"].toObject()["baseUrl"].toString();
        }
    };
}

#endif // PLAYBACKTRACKING_H
