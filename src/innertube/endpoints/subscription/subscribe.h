#pragma once
#include "innertube/endpoints/base/baseendpoint.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Subscribe or unsubscribe to/from one or multiple channels.
     */
    struct Subscribe : BaseEndpoint<"subscription/subscribe">
    {
        /**
         * @param params  Supplied by
         * @ref InnertubeObjects::SubscribeButton::onSubscribeEndpoints[0]["subscribeEndpoint"]["params"] if subscribing and
         * @ref InnertubeObjects::SubscribeButton::onUnsubscribeEndpoints[0]["signalServiceEndpoint"]["actions"][0]["openPopupAction"]["popup"]["confirmDialogRenderer"]["confirmButton"]["buttonRenderer"]["serviceEndpoint"]["unsubscribeEndpoint"] if unsubscribing.
         */
        static QJsonObject createBody(const InnertubeContext* context, const QStringList& channelIds, const QString& params);
    };
}
