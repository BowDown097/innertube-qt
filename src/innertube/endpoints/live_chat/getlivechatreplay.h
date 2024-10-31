#pragma once
#include "innertube/endpoints/base/baseendpoint.h"
#include <QJsonValue>

namespace InnertubeEndpoints
{
    /**
     * @brief Live chat data.
     */
    class GetLiveChatReplay : public BaseEndpoint<"live_chat/get_live_chat_replay">
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
        GetLiveChatReplay(const InnertubeContext* context, const InnertubeAuthStore* authStore,
                          const QString& continuation, const QString& playerOffsetMs);
    };
}
