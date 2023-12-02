#ifndef PLAYBACKTRACKING_H
#define PLAYBACKTRACKING_H
#include <QJsonValue>

namespace InnertubeObjects
{
    struct PlaybackTracking
    {
        QString atrUrl;
        QString ptrackingUrl;
        QString qoeUrl;
        QString videostatsDelayplayUrl;
        QString videostatsPlaybackUrl;
        QString videostatsWatchtimeUrl;

        PlaybackTracking() = default;
        explicit PlaybackTracking(const QJsonValue& playbackTracking)
            : atrUrl(playbackTracking["atrUrl"]["baseUrl"].toString()),
              ptrackingUrl(playbackTracking["ptrackingUrl"]["baseUrl"].toString()),
              qoeUrl(playbackTracking["qoeUrl"]["baseUrl"].toString()),
              videostatsDelayplayUrl(playbackTracking["videostatsDelayplayUrl"]["baseUrl"].toString()),
              videostatsPlaybackUrl(playbackTracking["videostatsPlaybackUrl"]["baseUrl"].toString()),
              videostatsWatchtimeUrl(playbackTracking["videostatsWatchtimeUrl"]["baseUrl"].toString()) {}
    };
}

#endif // PLAYBACKTRACKING_H
