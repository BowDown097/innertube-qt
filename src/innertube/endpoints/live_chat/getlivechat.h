#pragma once
#include "innertube/endpoints/base/baseendpoint.h"
#include <QJsonValue>

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
        GetLiveChat(const InnertubeContext* context, const InnertubeAuthStore* authStore, const QString& continuation);

        explicit GetLiveChat(const QJsonValue& data);
    private:
        static QJsonObject createBody(const InnertubeContext* context, const QString& continuation);
    };
}
