#ifndef NEXT_H
#define NEXT_H
#include <endpoints/base/baseendpoint.h>
#include <itc-objects/innertubeplaybackcontext.h>

namespace InnertubeEndpoints
{
    class Next : BaseEndpoint
    {
        friend class ::InnerTube;
    private:
        explicit Next(const QString& videoId, InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore)
        {
            easy->set(CURLOPT_URL, "https://www.youtube.com/youtubei/v1/next?key=AIzaSyAO_FJ2SlqU8Q4STEHLGCilw_Y9_11qcW8&prettyPrint=false");
            setNeededHeaders(easy, context, authStore);

            QJsonObject body = {
                { "autonavState", "STATE_ON" },
                { "captionsRequested", false },
                { "contentCheckOk", false },
                { "context", context->toJson() },
                { "playbackContext", InnertubePlaybackContext(false, "").toJson() },
                { "racyCheckOk", false },
                { "videoId", videoId }
            };

            QByteArray data;
            QByteArray bodyBytes = QJsonDocument(body).toJson(QJsonDocument::Compact);
            easy->set(CURLOPT_POSTFIELDS, bodyBytes.constData());
            easy->setWriteFunction([&data](char* d, size_t size)->size_t {
               data.append(d);
               return size;
            });

            easy->perform();
            QEventLoop event;
            QObject::connect(easy, &CurlEasy::done, &event, &QEventLoop::quit);
            event.exec();
        }
    };
}

#endif // NEXT_H
