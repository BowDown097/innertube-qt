#pragma once
#include "innertube/endpoints/base/baseendpoint.h"
#include <QJsonValue>

namespace InnertubeEndpoints
{
    /**
     * @brief Live chat data.
     */
    struct GetLiveChatReplay : BaseEndpoint<"live_chat/get_live_chat_replay">
    {
        QJsonValue liveChatContinuation;

        explicit GetLiveChatReplay(const QJsonValue& data);

        /**
         * @param continuationToken  Continuation token - supplied by @ref InnertubeObjects::LiveChat::continuations
         * or liveChatContinuation["continuations"][0]["invalidationContinuationData"]["continuation"].
         * @param playerOffsetMs  Position in the video in milliseconds
         */
        static QJsonObject createBody(
            const InnertubeContext* context, const QString& continuationToken, const QString& playerOffsetMs);
    };
}
