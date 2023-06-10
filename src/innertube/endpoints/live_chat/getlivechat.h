#ifndef GETLIVECHAT_H
#define GETLIVECHAT_H
#include "innertube/endpoints/base/baseendpoint.h"

namespace InnertubeEndpoints
{
    class GetLiveChat : public BaseEndpoint
    {
        friend class ::InnerTube;
    public:
        QJsonValue liveChatContinuation;
    private:
        GetLiveChat(const QString& continuation, InnertubeContext* context, InnertubeAuthStore* authStore);
    };
}

#endif // GETLIVECHAT_H
