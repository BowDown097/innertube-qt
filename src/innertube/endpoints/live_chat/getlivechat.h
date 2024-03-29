#ifndef GETLIVECHAT_H
#define GETLIVECHAT_H
#include "innertube/endpoints/base/baseendpoint.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Live chat data.
     */
    class GetLiveChat : public BaseEndpoint<"live_chat/get_live_chat">
    {
        friend class ::InnerTube;
    public:
        QJsonValue liveChatContinuation;
    protected:
        /**
         * @param continuation  Continuation token - supplied by @ref InnertubeObjects::LiveChat::continuations
         * or liveChatContinuation["continuations"][0]["invalidationContinuationData"]["continuation"].
         */
        GetLiveChat(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& continuation);
    };
}

#endif // GETLIVECHAT_H
