#ifndef GETLIVECHATREPLAY_H
#define GETLIVECHATREPLAY_H
#include "innertube/endpoints/base/baseendpoint.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Live chat data.
     */
    class GetLiveChatReplay : public BaseEndpoint
    {
        friend class ::InnerTube;
    public:
        QJsonValue liveChatContinuation;
    protected:
        /**
         * @param continuation  Continuation token - supplied by @ref InnertubeObjects::LiveChat::continuations
         * or liveChatContinuation["continuations"][0]["invalidationContinuationData"]["continuation"].
         * @param playerOffsetMs  Position in the video in milliseconds
         */
        GetLiveChatReplay(const QString& continuation, InnertubeContext* context,
                          InnertubeAuthStore* authStore, const QString& playerOffsetMs);
    };
}

#endif // GETLIVECHATREPLAY_H
