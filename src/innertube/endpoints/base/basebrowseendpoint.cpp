#include "basebrowseendpoint.h"
#include "innertube/innertubeexception.h"

namespace InnertubeEndpoints
{
    QJsonObject BaseBrowseEndpoint::_createBody(
        const InnertubeContext* context, const QString& browseId, const QString& continuationToken,
        const QString& query, const QString& params)
    {
        QJsonObject body = { { "context", context->toJson() } };
        if (continuationToken.isEmpty())
            body.insert("browseId", browseId);
        else
            body.insert("continuation", continuationToken);

        if (!query.isEmpty())
            body.insert("query", query);
        if (!params.isEmpty())
            body.insert("params", params);

        return body;
    }

    QJsonValue BaseBrowseEndpoint::getTabRenderer(const QJsonValue& contents, const QString& name)
    {
        const QJsonValue resultsRenderer = contents["twoColumnBrowseResultsRenderer"];
        if (!resultsRenderer.isObject())
            throw InnertubeException(QStringLiteral("[%1] twoColumnBrowseResultsRenderer not found").arg(name));

        const QJsonValue tabs = resultsRenderer["tabs"];
        if (!tabs.isArray())
            throw InnertubeException(QStringLiteral("[%1] tabs not found").arg(name));

        const QJsonValue tabRenderer = tabs[0]["tabRenderer"]["content"];
        if (!tabRenderer.isObject())
            throw InnertubeException(QStringLiteral("[%1] tabRenderer not found").arg(name));

        return tabRenderer;
    }
}
