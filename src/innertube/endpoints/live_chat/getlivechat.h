#ifndef GETLIVECHAT_H
#define GETLIVECHAT_H
#include "innertube/endpoints/base/baseendpoint.h"

namespace InnertubeEndpoints
{
     /**
     * @brief Live chat data.
     */
    class GetLiveChat : public BaseEndpoint
    {
        friend class ::InnerTube;
    public:
        QJsonValue liveChatContinuation;
    protected:
        /**
         * @param continuation  Continuation token - supplied by @ref InnertubeObjects::LiveChat::continuations
         * or liveChatContinuation["continuations"][0]["invalidationContinuationData"]["continuation"].
         */
        GetLiveChat(const QString& continuation, InnertubeContext* context, InnertubeAuthStore* authStore);
    };
}

#endif // GETLIVECHAT_H
