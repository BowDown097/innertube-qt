#include "baseendpoint.h"
#include <QFutureWatcher>
#include <QJsonDocument>
#include <QtConcurrent>

namespace InnertubeEndpoints
{
    QByteArray BaseEndpoint::get(const QString& endpoint, InnertubeContext* context, InnertubeAuthStore* authStore, const QJsonObject& body)
    {
        httplib::Client cli("https://www.youtube.com");
        setNeededHeaders(cli, context, authStore);
        return getData(cli, "/youtubei/v1/" + endpoint.toStdString() + "?key=AIzaSyAO_FJ2SlqU8Q4STEHLGCilw_Y9_11qcW8&prettyPrint=false", body);
    }

    QByteArray BaseEndpoint::getData(httplib::Client& client, const std::string& path, const QJsonObject& body)
    {
        const std::string bodyStr = QJsonDocument(body).toJson(QJsonDocument::Compact).toStdString();

        QFutureWatcher<std::string> watcher;
        watcher.setFuture(QtConcurrent::run([&client, path, bodyStr]() -> std::string {
            httplib::Result result = client.Post(path, bodyStr, "application/json");
            return result->body;
        }));

        QEventLoop event;
        QObject::connect(&watcher, &QFutureWatcher<std::string>::finished, &event, &QEventLoop::quit);
        event.exec();

        return QByteArray::fromStdString(watcher.result());
    }

    void BaseEndpoint::setNeededHeaders(httplib::Client& client, InnertubeContext* context, InnertubeAuthStore* authStore)
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

        client.set_default_headers(headers);
    }
}

