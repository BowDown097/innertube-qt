#include "baseendpoint.h"
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    void BaseEndpoint::get(const QString& endpoint, InnertubeContext* context, InnertubeAuthStore* authStore, CurlEasy* easy,
                           const QJsonObject& body, QByteArray& data)
    {
        easy->set(CURLOPT_URL, QStringLiteral("https://www.youtube.com/youtubei/v1/%1?key=%2&prettyPrint=false")
                               .arg(endpoint, keyFor(context->client.clientName)));
        setNeededHeaders(easy, context, authStore);
        getData(easy, body, data);
    }

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

    QString BaseEndpoint::keyFor(const QString& client) const
    {
        if (auto key_itr = CLIENT_KEYS.find(client); key_itr != CLIENT_KEYS.end())
        {
            if (client != "WEB" && client != "ANDROID")
            {
                qWarning() << "Key found for input client" << client << "which is not WEB or ANDROID. "
                              "Understand that innertube-qt is built for those clients, "
                              "and thus endpoint response members may not be what you expect.";
            }
            return *key_itr;
        }
        else
        {
            throw std::range_error("No key found for client " + client.toStdString());
        }
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
