#ifndef BASEENDPOINT_H
#define BASEENDPOINT_H
#include <itc-objects/innertubeauthstore.h>
#include <innertubeexception.hpp>
#include <QJsonDocument>

class InnerTube;
namespace InnertubeEndpoints
{
    class BaseEndpoint
    {
    protected:
        void setNeededHeaders(CurlEasy* easy, InnertubeContext* context, InnertubeAuthStore* authStore)
        {
            if (authStore->populated)
            {
                easy->setHttpHeaderRaw("Authorization", authStore->generateSAPISIDHash().toUtf8());
                easy->setHttpHeaderRaw("Cookie", authStore->getNecessaryLoginCookies().toUtf8());
                easy->setHttpHeaderRaw("X-Goog-AuthUser", "0");
            }

            easy->setHttpHeaderRaw("Content-Type", "application/json");
            easy->setHttpHeaderRaw("X-Goog-Visitor-Id", context->client.visitorData.toLatin1());
            easy->setHttpHeaderRaw("X-YOUTUBE-CLIENT-NAME", context->client.clientName.toLatin1());
            easy->setHttpHeaderRaw("X-YOUTUBE-CLIENT-VERSION", context->client.clientVersion.toLatin1());
            easy->setHttpHeaderRaw("X-ORIGIN", "https://www.youtube.com");
        }
    };
}

#endif // BASEENDPOINT_H
