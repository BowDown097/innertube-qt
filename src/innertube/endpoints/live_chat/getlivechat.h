#ifndef GETLIVECHAT_H
#define GETLIVECHAT_H
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/responses/live_chat/livechatresponse.h"

namespace InnertubeEndpoints
{
    class GetLiveChat : public BaseEndpoint
    {
        friend class ::InnerTube;
    public:
        LiveChatResponse response;
    private:
        GetLiveChat(const QString& continuation, InnertubeContext* context, InnertubeAuthStore* authStore);
    };
}

#endif // GETLIVECHAT_H
