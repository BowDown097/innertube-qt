#include "resolveurl.h"
#include "innertube/innertubeexception.h"
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    ResolveUrl::ResolveUrl(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& url)
    {
        QJsonObject body = { EndpointMethods::contextPair(context) };
        if (QUrl urlObj(url); urlObj.isValid())
        {
            if (urlObj.isRelative())
            {
                urlObj.setHost("www.youtube.com");
                urlObj.setScheme("https");

                if (!urlObj.isValid())
                    throw InnertubeException(QStringLiteral("[ResolveUrl] Failed to construct URL: %1").arg(urlObj.errorString()));
            }

            body.insert("url", urlObj.toString());

            const QJsonValue data = get(context, authStore, body);
            if (data["error"].isObject())
                throw InnertubeException(QStringLiteral("[ResolveUrl] %1: %2").arg(data["code"].toInt()).arg(data["message"].toString()));
            if (!data["endpoint"].isObject())
                throw InnertubeException("[ResolveUrl] Endpoint object is missing. Pretty sure this is bad.");

            endpoint = data["endpoint"];
        }
        else
        {
            throw InnertubeException(QStringLiteral("[ResolveUrl] Invalid URL: %1").arg(url));
        }
    }
}
