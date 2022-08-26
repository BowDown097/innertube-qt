#ifndef BASEENDPOINT_H
#define BASEENDPOINT_H
#include <itc-objects/innertubeauthstore.h>
#include <innertubeexception.hpp>
#include <QJsonDocument>
#include <QtNetwork>

class InnerTube;
namespace InnertubeEndpoints
{
    class BaseEndpoint
    {
    protected:
        void setNeededHeaders(QNetworkRequest& request, InnertubeContext* context, InnertubeAuthStore* authStore)
        {
            if (authStore->populated)
            {
                request.setRawHeader("Authorization", authStore->generateSAPISIDHash().toUtf8());
                request.setRawHeader("Cookie", authStore->getNecessaryLoginCookies().toUtf8());
                request.setRawHeader("X-Goog-AuthUser", "0");
            }

            request.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain;charset=UTF-8");
            request.setRawHeader("X-Goog-Visitor-Id", context->client.visitorData.toLatin1());
            request.setRawHeader("X-YOUTUBE-CLIENT-NAME", context->client.clientName.toLatin1());
            request.setRawHeader("X-YOUTUBE-CLIENT-VERSION", context->client.clientVersion.toLatin1());
            request.setRawHeader("X-ORIGIN", "https://www.youtube.com");
        }
    };
}

#endif // BASEENDPOINT_H
