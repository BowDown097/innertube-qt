#include "baseendpoint.h"
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    QByteArray BaseEndpoint::get(const QString& endpoint, InnertubeContext* context, InnertubeAuthStore* authStore, const QJsonObject& body)
    {
        qthttplib::Client* cli = new qthttplib::Client("https://www.youtube.com");
        setNeededHeaders(cli, context, authStore);
        return getData(cli, "/youtubei/v1/" + endpoint + "?key=AIzaSyAO_FJ2SlqU8Q4STEHLGCilw_Y9_11qcW8&prettyPrint=false", body);
    }

    QByteArray BaseEndpoint::getData(qthttplib::Client* client, const QString& path, const QJsonObject& body)
    {
        QByteArray data;
        client->post(path, QJsonDocument(body).toJson(QJsonDocument::Compact), "application/json");

        QEventLoop event;
        QObject::connect(client, &qthttplib::Client::requestFinished, &event, [&data, &event](const qthttplib::Response& response) {
            event.quit();
            data = response.body;
        });
        event.exec();

        return data;
    }

    void BaseEndpoint::setNeededHeaders(qthttplib::Client* client, InnertubeContext* context, InnertubeAuthStore* authStore)
    {
        httplib::Headers headers;

        if (authStore->populated)
        {
            headers.insert({
                { "Authorization", authStore->generateSAPISIDHash().toStdString() },
                { "Cookie", authStore->getNecessaryLoginCookies().toStdString() },
                { "X-Goog-AuthUser", "0" }
            });
        }

        headers.insert({
            { "X-Goog-Visitor-Id", context->client.visitorData.toStdString() },
            { "X-YOUTUBE-CLIENT-NAME", context->client.clientName.toStdString() },
            { "X-YOUTUBE-CLIENT-VERSION", context->client.clientVersion.toStdString() },
            { "X-ORIGIN", "https://www.youtube.com" }
        });

        client->set_default_headers(headers);
    }
}

