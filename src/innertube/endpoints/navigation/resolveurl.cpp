#include "resolveurl.h"
#include "innertube/innertubeexception.h"

namespace InnertubeEndpoints
{
    ResolveUrl::ResolveUrl(const InnertubeContext* context, const InnertubeAuthStore* authStore, const QString& url)
        : ResolveUrl(get(context, authStore, createBody(context, url))) {}

    ResolveUrl::ResolveUrl(const QJsonValue& data)
    {
        if (const QJsonValue error = data["error"]; error.isObject())
        {
            throw InnertubeException(QStringLiteral("[ResolveUrl] Error %1: %2")
                .arg(error["code"].toInt()).arg(error["message"].toString()));
        }

        if (!data["endpoint"].isObject())
            throw InnertubeException("[ResolveUrl] Endpoint object is missing with no error. Pretty sure this is bad.");

        endpoint = data["endpoint"];
    }

    QJsonObject ResolveUrl::createBody(const InnertubeContext* context, const QString& url)
    {
        QJsonObject body = { EndpointMethods::contextPair(context) };
        QUrl urlObj(url);
        if (!urlObj.isValid())
            throw InnertubeException(QStringLiteral("[ResolveUrl] Invalid URL: %1").arg(url));

        if (urlObj.isRelative())
        {
            // for some reason, Qt needs / at the beginning of the path otherwise this fails
            if (QString path = urlObj.path(); !path.startsWith('/'))
                urlObj.setPath(path.prepend('/'));

            urlObj.setHost("www.youtube.com");
            urlObj.setScheme("https");

            if (!urlObj.isValid())
                throw InnertubeException(QStringLiteral("[ResolveUrl] Failed to construct URL: %1").arg(urlObj.errorString()));
        }

        body.insert("url", urlObj.toString());
        return body;
    }
}
