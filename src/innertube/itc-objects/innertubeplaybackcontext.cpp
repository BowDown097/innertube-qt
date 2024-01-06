#include "innertubeplaybackcontext.h"
#ifdef INNERTUBE_GET_STS
#include <QtNetwork/QtNetwork>
#endif

QJsonObject InnertubePlaybackContext::toJson() const
{
    if (!isContent)
    {
        return {
            { "lactMilliseconds", lactMilliseconds },
            { "vis", vis }
        };
    }
    else
    {
        return {
            { "contentPlaybackContext", QJsonObject {
                { "currentUrl", currentUrl },
                { "html5Preference", html5Preference },
#ifdef INNERTUBE_GET_STS
                { "signatureTimestamp", signatureTimestamp != 0 ? signatureTimestamp : fetchSignatureTimestamp() },
#endif
                { "referer", referer }
            } }
        };
    }
}

#ifdef INNERTUBE_GET_STS
int InnertubePlaybackContext::fetchSignatureTimestamp() const
{
    QNetworkAccessManager* man = new QNetworkAccessManager;

    // get the body of the embed for "Me at the zoo", which is almost guaranteed to never go down as long as YouTube exists
    QNetworkReply* embedReply = man->get(QNetworkRequest(QUrl("https://www.youtube.com/embed/jNQXAC9IVRw")));

    QEventLoop embedLoop;
    QObject::connect(embedReply, &QNetworkReply::finished, &embedLoop, &QEventLoop::quit);
    embedLoop.exec();

    QByteArray embedBody = embedReply->readAll();
    embedReply->deleteLater();

    // extract application URL
    static QRegularExpression playerJsRegex("/s/player/[a-zA-Z0-9/\\-_.]*base.js");
    QRegularExpressionMatch match = playerJsRegex.match(embedBody);
    QUrl playerJsUrl("https://www.youtube.com" + match.captured());

    // get the application body
    QNetworkReply* appReply = man->get(QNetworkRequest(playerJsUrl));

    QEventLoop appLoop;
    QObject::connect(appReply, &QNetworkReply::finished, &appLoop, &QEventLoop::quit);
    appLoop.exec();

    QByteArray appBody = appReply->readAll();
    appReply->deleteLater();
    man->deleteLater();

    // extract and return the sts body
    static QRegularExpression stsRegex("signatureTimestamp:?\\s*([0-9]*)");
    QRegularExpressionMatch stsMatch = stsRegex.match(appBody);
    return stsMatch.captured(1).toInt();
}
#endif
