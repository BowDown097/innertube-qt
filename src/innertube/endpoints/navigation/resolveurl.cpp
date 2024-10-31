#include "resolveurl.h"
#include "innertube/innertubeexception.h"

namespace InnertubeEndpoints
{
    ResolveUrl::ResolveUrl(const InnertubeContext* context, const InnertubeAuthStore* authStore, const QString& url)
    {
        QJsonObject body = { EndpointMethods::contextPair(context) };
        if (QUrl urlObj(url); urlObj.isValid())
        {
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

            const QJsonValue data = get(context, authStore, body);
            if (data["error"].isObject())
            {
                throw InnertubeException(QStringLiteral("[ResolveUrl] Error %1: %2")
                    .arg(data["error"]["code"].toInt()).arg(data["error"]["message"].toString()));
            }
            if (!data["endpoint"].isObject())
            {
                throw InnertubeException("[ResolveUrl] Endpoint object is missing with no error. Pretty sure this is bad.");
            }

            endpoint = data["endpoint"];
        }
        else
        {
            throw InnertubeException(QStringLiteral("[ResolveUrl] Invalid URL: %1").arg(url));
        }
    }
}
