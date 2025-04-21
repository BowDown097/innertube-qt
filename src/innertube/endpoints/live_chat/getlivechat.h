#pragma once
#include "innertube/endpoints/base/baseendpoint.h"
#include <QJsonValue>

namespace InnertubeEndpoints
{
    /**
     * @brief Live chat data.
     */
    struct GetLiveChat : BaseEndpoint<"live_chat/get_live_chat">
    {
        QJsonValue liveChatContinuation;

        explicit GetLiveChat(const QJsonValue& data);

        /**
         * @param continuationToken  Continuation token - supplied by @ref InnertubeObjects::LiveChat::continuations
         * or liveChatContinuation["continuations"][0]["invalidationContinuationData"]["continuation"].
         */
        static QJsonObject createBody(const InnertubeContext* context, const QString& continuationToken);
    };
}
