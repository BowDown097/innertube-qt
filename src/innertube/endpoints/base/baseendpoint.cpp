#include "baseendpoint.h"
#include <QEventLoop>
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    QByteArray BaseEndpoint::get(const QString& endpoint, InnertubeContext* context, InnertubeAuthStore* authStore, const QJsonObject& body)
    {
        return getData("https://www.youtube.com/youtubei/v1/" + endpoint + "?key=AIzaSyAO_FJ2SlqU8Q4STEHLGCilw_Y9_11qcW8&prettyPrint=false",
                       std::move(getNeededHeaders(context, authStore)), body);
    }

    QByteArray BaseEndpoint::getData(const QString& path, const QMap<QString, QString>& headers, const QJsonObject& body)
    {
        SslHttpRequest* req = new SslHttpRequest(path, SslHttpRequest::RequestMethod::Post);
        req->setBody(body);
        req->setHeaders(headers);
        req->send();

        QEventLoop loop;
        QObject::connect(req, &SslHttpRequest::finished, &loop, &QEventLoop::quit);
        loop.exec();

        QByteArray data = req->payload();
        req->deleteLater();
        return data;
    }

    QMap<QString, QString> BaseEndpoint::getNeededHeaders(InnertubeContext* context, InnertubeAuthStore* authStore)
    {
        QMap<QString, QString> headers;

        if (authStore->populated)
        {
            headers.insert({
                { "Authorization", authStore->generateSAPISIDHash() },
                { "Cookie", authStore->getNecessaryLoginCookies() },
                { "X-Goog-AuthUser", "0" }
            });
        }

        headers.insert({
            { "X-Goog-Visitor-Id", context->client.visitorData },
            { "X-YOUTUBE-CLIENT-NAME", context->client.clientName },
            { "X-YOUTUBE-CLIENT-VERSION", context->client.clientVersion },
            { "X-ORIGIN", "https://www.youtube.com" }
        });

        return headers;
    }
}

