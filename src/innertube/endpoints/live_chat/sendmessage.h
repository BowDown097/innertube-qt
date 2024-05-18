#pragma once
#include "innertube/endpoints/base/baseendpoint.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    /**
     * @brief Send a live chat message.
     */
    class SendMessage : public BaseEndpoint<"live_chat/send_message">
    {
        friend class ::InnerTube;
    protected:
        /**
         * @details In parameter details, @ref InnertubeEndpoints::GetLiveChat::liveChatContinuation["actionPanel"]["liveChatMessageInputRenderer"]["sendButton"]["buttonRenderer"]["serviceEndpoint"]["sendLiveChatMessageEndpoint"]
         * is simply expressed as "sendEndpoint."
         * @param textSegments  See [QtTube code](https://github.com/search?q=repo%3ABowDown097%2FQtTube+producerichtext&type=code) for usage.
         * @param clientMessageId  Supplied by sendEndpoint["clientIdPrefix"]
         * followed by the number of messages sent by the user in the current live chat session.
         * @param params  Supplied by sendEndpoint["params"].
         */
        SendMessage(const QJsonArray& textSegments, InnertubeContext* context, InnertubeAuthStore* authStore,
                    const QString& clientMessageId, const QString& params);
        /**
         * @brief Overload of main constructor just for text.
         * @details See previous constructor for parameter details.
         */
        SendMessage(const QString& message, InnertubeContext* context, InnertubeAuthStore* authStore,
                    const QString& clientMessageId, const QString& params);
    };
}
