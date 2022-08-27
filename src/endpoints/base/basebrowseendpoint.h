#ifndef BASEBROWSEENDPOINT_H
#define BASEBROWSEENDPOINT_H
#include "baseendpoint.h"

namespace InnertubeEndpoints
{
    class BaseBrowseEndpoint : public BaseEndpoint
    {
    protected:
        QByteArray data;
        explicit BaseBrowseEndpoint(const QString& browseId, InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore)
        {
            easy->set(CURLOPT_URL, "https://www.youtube.com/youtubei/v1/browse?key=AIzaSyAO_FJ2SlqU8Q4STEHLGCilw_Y9_11qcW8&prettyPrint=false");
            setNeededHeaders(easy, context, authStore);

            QJsonObject body = {
                { "context", context->toJson() },
                { "browseId", browseId }
            };

            QByteArray bodyBytes = QJsonDocument(body).toJson(QJsonDocument::Compact);
            easy->set(CURLOPT_POSTFIELDS, bodyBytes.constData());
            easy->setWriteFunction([this](char* d, size_t size)->size_t {
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

#endif // BASEBROWSEENDPOINT_H
