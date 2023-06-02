#include "baseendpoint.h"
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    QByteArray BaseEndpoint::get(const QString& endpoint, InnertubeContext* context, InnertubeAuthStore* authStore, const QJsonObject& body)
    {
        return getData("https://www.youtube.com/youtubei/v1/" + endpoint + "?key=AIzaSyAO_FJ2SlqU8Q4STEHLGCilw_Y9_11qcW8&prettyPrint=false",
                       std::move(getNeededHeaders(context, authStore)), body);
    }

    QByteArray BaseEndpoint::getData(const QString& path, const cpr::Header& headers, const QJsonObject& body)
    {
        cpr::Response r = cpr::Post(cpr::Url{path.toStdString()}, cpr::Body{QJsonDocument(body).toJson(QJsonDocument::Compact)}, headers);
        return QByteArray::fromStdString(r.text);
    }

    cpr::Header BaseEndpoint::getNeededHeaders(InnertubeContext* context, InnertubeAuthStore* authStore)
    {
        cpr::Header headers;

        if (authStore->populated)
        {
            headers.insert({
                { "Authorization", authStore->generateSAPISIDHash().toStdString() },
                { "Cookie", authStore->getNecessaryLoginCookies().toStdString() },
                { "X-Goog-AuthUser", "0" }
            });
        }

        headers.insert({
            { "Content-Type", "application/json" },
            { "X-Goog-Visitor-Id", context->client.visitorData.toStdString() },
            { "X-YOUTUBE-CLIENT-NAME", context->client.clientName.toStdString() },
            { "X-YOUTUBE-CLIENT-VERSION", context->client.clientVersion.toStdString() },
            { "X-ORIGIN", "https://www.youtube.com" }
        });

        return headers;
    }
}

