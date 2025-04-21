#pragma once
#include "innertube/endpoints/base/baseendpoint.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Send a live chat message.
     */
    struct SendMessage : BaseEndpoint<"live_chat/send_message">
    {
        QJsonValue data;

        explicit SendMessage(const QJsonValue& data);

        /**
         * @details In parameter details, @ref InnertubeEndpoints::GetLiveChat::liveChatContinuation["actionPanel"]["liveChatMessageInputRenderer"]["sendButton"]["buttonRenderer"]["serviceEndpoint"]["sendLiveChatMessageEndpoint"]
         * is simply expressed as "sendEndpoint."
         * @param textSegments  See [QtTube code](https://github.com/search?q=repo%3ABowDown097%2FQtTube+producerichtext&type=code) for usage.
         * @param clientMessageId  Supplied by sendEndpoint["clientIdPrefix"]
         * followed by the number of messages sent by the user in the current live chat session.
         * @param params  Supplied by sendEndpoint["params"].
         */
        static QJsonObject createBody(
            const InnertubeContext* context, const QJsonArray& textSegments,
            const QString& clientMessageId, const QString& params);

        /**
         * @brief Overload of createBody() just for text.
         * @details See primary definition for parameter details.
         */
        static QJsonObject createBody(
            const InnertubeContext* context, const QString& message,
            const QString& clientMessageId, const QString& params);
    };
}
