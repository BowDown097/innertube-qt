#include "innertubeplaybackcontext.h"
#include <QJsonObject>

#ifdef INNERTUBE_GET_STS
#include "http.h"
#include <QEventLoop>
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
    // get the body of the embed for "Me at the zoo", which is almost guaranteed to never go down as long as YouTube exists
    const HttpReply* embedReply = Http::instance().get(QUrl("https://www.youtube.com/embed/jNQXAC9IVRw"));

    QEventLoop embedLoop;
    QObject::connect(embedReply, &HttpReply::finished, &embedLoop, &QEventLoop::quit);
    embedLoop.exec();

    QByteArray embedBody = embedReply->body();

    // extract application URL
    static QRegularExpression playerJsRegex("/s/player/[a-zA-Z0-9/\\-_.]*base.js");
    QRegularExpressionMatch match = playerJsRegex.match(embedBody);
    QUrl playerJsUrl("https://www.youtube.com" + match.captured());

    // get the application body
    const HttpReply* appReply = Http::instance().get(playerJsUrl);

    QEventLoop appLoop;
    QObject::connect(appReply, &HttpReply::finished, &appLoop, &QEventLoop::quit);
    appLoop.exec();

    QByteArray appBody = appReply->body();

    // extract and return the sts body
    static QRegularExpression stsRegex("signatureTimestamp:?\\s*([0-9]*)");
    QRegularExpressionMatch stsMatch = stsRegex.match(appBody);
    return stsMatch.captured(1).toInt();
}
#endif
