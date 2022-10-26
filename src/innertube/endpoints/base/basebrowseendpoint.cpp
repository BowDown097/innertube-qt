#include "basebrowseendpoint.h"
#include "innertube/innertubeexception.h"
#include <QJsonArray>
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    BaseBrowseEndpoint::BaseBrowseEndpoint(const QString& browseId, InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore, const QString& continuationToken)
    {
        QJsonObject body = {{ "context", context->toJson() }};
        if (continuationToken.isEmpty())
            body.insert("browseId", browseId);
        else
            body.insert("continuation", continuationToken);
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
        if (tabs.count() != 1)
            throw InnertubeException(QStringLiteral("[%1] Expected 1 element in tabs, got %2").arg(name, tabs.count()));

        QJsonObject tabRenderer = tabs[0].toObject()["tabRenderer"].toObject()["content"].toObject();
        if (tabRenderer.isEmpty())
            throw InnertubeException(QStringLiteral("[%1] tabRenderer not found").arg(name));

        return tabRenderer;
    }
}
