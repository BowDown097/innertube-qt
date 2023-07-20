#ifndef INNERTUBEPLAYBACKCONTEXT_H
#define INNERTUBEPLAYBACKCONTEXT_H
#include <QJsonObject>
#include <QString>

class InnertubePlaybackContext
{
public:
    QString currentUrl;
    QString html5Preference;
    bool isContent;
    QString lactMilliseconds;
    QString referer;
    int signatureTimestamp;
    int vis;

    InnertubePlaybackContext(bool isContent, const QString& currentUrl, int signatureTimestamp = 0,
                             const QString& html5Preference = "HTML5_PREF_WANTS", const QString& lactMilliseconds = "-1",
                             const QString& referer = "https://www.youtube.com/", int vis = 0)
        : currentUrl(currentUrl),
          html5Preference(html5Preference),
          isContent(isContent),
          lactMilliseconds(lactMilliseconds),
          referer(referer),
          signatureTimestamp(signatureTimestamp),
          vis(vis) {}
    QJsonObject toJson() const;
#ifdef INNERTUBE_GET_STS
private:
    int fetchSignatureTimestamp() const;
#endif
};

#endif // INNERTUBEPLAYBACKCONTEXT_H
