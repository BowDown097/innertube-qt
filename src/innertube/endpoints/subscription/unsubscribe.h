#pragma once
#include "innertube/endpoints/base/baseendpoint.h"

namespace InnertubeEndpoints
{
    struct Unsubscribe : BaseEndpoint<"subscription/unsubscribe">
    {
        /**
         * @param params  Supplied by
         * @ref InnertubeObjects::SubscribeButton::onUnsubscribeEndpoints[0]["signalServiceEndpoint"]["actions"][0]["openPopupAction"]["popup"]["confirmDialogRenderer"]["confirmButton"]["buttonRenderer"]["serviceEndpoint"]["unsubscribeEndpoint"] if unsubscribing.
         */
        static QJsonObject createBody(const InnertubeContext* context, const QStringList& channelIds, const QString& params);
    };
}
