#ifndef INNERTUBEPLAYBACKCONTEXT_H
#define INNERTUBEPLAYBACKCONTEXT_H
#include <QJsonObject>
#include <QString>

class InnertubePlaybackContext
{
public:
    bool autoCaptionsDefaultOn, isContent, splay;
    int vis;
    QString autonavState, currentUrl, html5Preference, lactMilliseconds, referer;

    InnertubePlaybackContext(bool isContent, const QString& currentUrl, bool autoCaptionsDefaultOn = false, const QString& autonavState = "STATE_ON",
                             const QString& html5Preference = "HTML5_PREF_WANTS", const QString& lactMilliseconds = "-1",
                             const QString& referer = "https://www.youtube.com/", bool splay = false, int vis = 0)
        : autoCaptionsDefaultOn(autoCaptionsDefaultOn), isContent(isContent), splay(splay), vis(vis), autonavState(autonavState), currentUrl(currentUrl),
          html5Preference(html5Preference), lactMilliseconds(lactMilliseconds), referer(referer) {}
    QJsonObject toJson() const;
};

#endif // INNERTUBEPLAYBACKCONTEXT_H
