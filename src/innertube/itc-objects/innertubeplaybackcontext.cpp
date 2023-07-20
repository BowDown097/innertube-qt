#include "innertubeplaybackcontext.h"
#ifdef INNERTUBE_GET_STS
#include "sslhttprequest.h"
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
    QScopedPointer<SslHttpRequest, QScopedPointerDeleteLater> embedReq(new SslHttpRequest("https://www.youtube.com/embed/jNQXAC9IVRw"));
    embedReq->send();

    QEventLoop embedLoop;
    QObject::connect(embedReq.data(), &SslHttpRequest::finished, &embedLoop, &QEventLoop::quit);
    embedLoop.exec();

    QByteArray embedBody = embedReq->payload();

    // extract application URL
    static QRegularExpression playerJsRegex("/s/player/[a-zA-Z0-9/\\-_.]*base.js");
    QRegularExpressionMatch match = playerJsRegex.match(embedBody);
    QString playerJsUrl = "https://www.youtube.com" + match.captured();

    // get the application body
    QScopedPointer<SslHttpRequest, QScopedPointerDeleteLater> appReq(new SslHttpRequest(playerJsUrl));
    appReq->send();

    QEventLoop appLoop;
    QObject::connect(appReq.data(), &SslHttpRequest::finished, &appLoop, &QEventLoop::quit);
    appLoop.exec();

    QByteArray appBody = appReq->payload();

    // extract and return the sts body
    static QRegularExpression stsRegex("signatureTimestamp:?\\s*([0-9]*)");
    QRegularExpressionMatch stsMatch = stsRegex.match(appBody);
    return stsMatch.captured(1).toInt();
}
#endif
