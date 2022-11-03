#include "basebrowseendpoint.h"
#include "innertube/innertubeexception.h"
#include <QJsonArray>
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    BaseBrowseEndpoint::BaseBrowseEndpoint(const QString& browseId, InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore,
                                           const QString& continuationToken, const QString& query)
    {
        QJsonObject body = {{ "context", context->toJson() }};

        if (continuationToken.isEmpty())
            body.insert("browseId", browseId);
        else
            body.insert("continuation", continuationToken);

        if (!query.isEmpty())
            body.insert("query", query);

        get("browse", context, authStore, easy, body, data);
    }

    QJsonObject BaseBrowseEndpoint::getTabRenderer(const QString& name, const QString& baseRenderer)
    {
        QJsonObject contents = QJsonDocument::fromJson(data).object()["contents"].toObject();
        if (contents.isEmpty())
            throw InnertubeException(QStringLiteral("[%1] contents not found").arg(name));

        QJsonObject resultsRenderer = contents[baseRenderer].toObject();
        if (resultsRenderer.isEmpty())
            throw InnertubeException(QStringLiteral("[%1] %2 not found").arg(name, baseRenderer));

        QJsonArray tabs = resultsRenderer["tabs"].toArray();
        if (tabs.isEmpty())
            throw InnertubeException(QStringLiteral("[%1] tabs not found or is empty").arg(name));

        QJsonObject tabRenderer = tabs[0].toObject()["tabRenderer"].toObject()["content"].toObject();
        if (tabRenderer.isEmpty())
            throw InnertubeException(QStringLiteral("[%1] tabRenderer not found").arg(name));

        return tabRenderer;
    }
}
