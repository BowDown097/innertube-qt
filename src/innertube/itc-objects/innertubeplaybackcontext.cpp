#include "innertubeplaybackcontext.h"
#ifdef GETSTS
#include "CurlEasy.h"
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
#ifdef GETSTS
                { "signatureTimestamp", signatureTimestamp != 0 ? signatureTimestamp : fetchSignatureTimestamp() },
#endif
                { "referer", referer }
            } }
        };
    }
}

#ifdef GETSTS
int InnertubePlaybackContext::fetchSignatureTimestamp() const
{
    // get the body of the embed for "Me at the zoo", which is almost guaranteed to never go down as long as YouTube exists
    QString embedBody;
    CurlEasy* easy = new CurlEasy;
    easy->set(CURLOPT_URL, "https://www.youtube.com/embed/jNQXAC9IVRw");
    easy->setWriteFunction([&embedBody](char* d, size_t size)->size_t { embedBody.append(d); return size; });
    easy->perform();
    QEventLoop event;
    QObject::connect(easy, &CurlEasy::done, &event, &QEventLoop::quit);
    event.exec();

    // extract application URL
    QRegularExpressionMatch match = playerJsRegex.match(embedBody);
    QString playerJsUrl = "https://www.youtube.com" + match.captured();

    // get the application body
    QString appBody;
    easy->set(CURLOPT_URL, playerJsUrl);
    easy->setWriteFunction([&appBody](char* d, size_t size)->size_t { appBody.append(d); return size; });
    easy->perform();
    QEventLoop appEvent;
    QObject::connect(easy, &CurlEasy::done, &appEvent, &QEventLoop::quit);
    appEvent.exec();

    // extract the sts body
    QRegularExpressionMatch stsMatch = signatureTimestampRegex.match(appBody);
    long signatureTimestamp = stsMatch.captured(1).toInt();

    // clean up and return
    easy->deleteLater();
    return signatureTimestamp;
}
#endif
