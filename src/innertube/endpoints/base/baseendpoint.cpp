#include "baseendpoint.h"
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    void BaseEndpoint::getData(CurlEasy* easy, const QJsonObject& body, QByteArray& data)
    {
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

    void BaseEndpoint::setNeededHeaders(CurlEasy* easy, InnertubeContext* context, InnertubeAuthStore* authStore)
    {
        if (authStore->populated)
        {
            easy->setHttpHeaderRaw("Authorization", authStore->generateSAPISIDHash().toUtf8());
            easy->setHttpHeaderRaw("Cookie", authStore->getNecessaryLoginCookies().toUtf8());
            easy->setHttpHeaderRaw("X-Goog-AuthUser", "0");
        }

        easy->setHttpHeaderRaw("Content-Type", "application/json");
        easy->setHttpHeaderRaw("X-Goog-Visitor-Id", context->client.visitorData.toLatin1());
        easy->setHttpHeaderRaw("X-YOUTUBE-CLIENT-NAME", context->client.clientName.toLatin1());
        easy->setHttpHeaderRaw("X-YOUTUBE-CLIENT-VERSION", context->client.clientVersion.toLatin1());
        easy->setHttpHeaderRaw("X-ORIGIN", "https://www.youtube.com");
    }
}
