#ifndef BASEBROWSEENDPOINT_H
#define BASEBROWSEENDPOINT_H
#include "baseendpoint.h"
#include <objects/video/video.h>

namespace InnertubeEndpoints
{
    class BaseBrowseEndpoint : public BaseEndpoint
    {
    protected:
        QByteArray data;
        BaseBrowseEndpoint(const QString& browseId, InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore, const QString& continuationToken = "")
        {
            easy->set(CURLOPT_URL, "https://www.youtube.com/youtubei/v1/browse?key=AIzaSyAO_FJ2SlqU8Q4STEHLGCilw_Y9_11qcW8&prettyPrint=false");
            setNeededHeaders(easy, context, authStore);

            QJsonObject body = {{ "context", context->toJson() }};
            if (continuationToken.isEmpty())
                body.insert("browseId", browseId);
            else
                body.insert("continuation", continuationToken);

            getData(easy, body, data);
        }

        QJsonObject getTabRenderer(const QString& name, const QString& baseRenderer = "twoColumnBrowseResultsRenderer")
        {
            QJsonObject contents = QJsonDocument::fromJson(data).object()["contents"].toObject();
            if (contents.isEmpty())
                throw InnertubeException(QStringLiteral("[%1] contents not found").arg(name));

            QJsonObject resultsRenderer = contents[baseRenderer].toObject();
            if (resultsRenderer.isEmpty())
                throw InnertubeException(QStringLiteral("[%1] %2 not found").arg(name, baseRenderer));

            QJsonArray tabs = resultsRenderer["tabs"].toArray();
            if (tabs.count() != 1)
                throw InnertubeException(QStringLiteral("[%1] Expected 1 element in tabs, got %2").arg(name, tabs.count()));

            QJsonObject tabRenderer = tabs[0].toObject()["tabRenderer"].toObject()["content"].toObject();
            if (tabRenderer.isEmpty())
                throw InnertubeException(QStringLiteral("[%1] tabRenderer not found").arg(name));

            return tabRenderer;
        }
    };
}

#endif // BASEBROWSEENDPOINT_H
