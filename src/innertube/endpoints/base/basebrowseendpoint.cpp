#include "basebrowseendpoint.h"
#include "innertube/innertubeexception.h"
#include <QJsonArray>
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    BaseBrowseEndpoint::BaseBrowseEndpoint(const QString& browseId, InnertubeContext* context, InnertubeAuthStore* authStore,
                                           const QString& continuationToken, const QString& query)
    {
        QJsonObject body = {{ "context", context->toJson() }};

        if (continuationToken.isEmpty())
            body.insert("browseId", browseId);
        else
            body.insert("continuation", continuationToken);

        if (!query.isEmpty())
            body.insert("query", query);

        data = get("browse", context, authStore, body);
    }

    QJsonObject BaseBrowseEndpoint::getTabRenderer(const QString& name) const
    {
        const QJsonObject contents = QJsonDocument::fromJson(data).object()["contents"].toObject();
        if (contents.isEmpty())
            throw InnertubeException(QStringLiteral("[%1] contents not found").arg(name));

        const QJsonObject resultsRenderer = contents["twoColumnBrowseResultsRenderer"].toObject();
        if (resultsRenderer.isEmpty())
            throw InnertubeException(QStringLiteral("[%1] twoColumnBrowseResultsRenderer not found").arg(name));

        const QJsonArray tabs = resultsRenderer["tabs"].toArray();
        if (tabs.isEmpty())
            throw InnertubeException(QStringLiteral("[%1] tabs not found or is empty").arg(name));

        const QJsonObject tabRenderer = tabs[0]["tabRenderer"]["content"].toObject();
        if (tabRenderer.isEmpty())
            throw InnertubeException(QStringLiteral("[%1] tabRenderer not found").arg(name));

        return tabRenderer;
    }
}
