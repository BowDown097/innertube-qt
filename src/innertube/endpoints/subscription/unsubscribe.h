#pragma once
#include "innertube/endpoints/base/baseendpoint.h"

namespace InnertubeEndpoints
{
    class Unsubscribe : public BaseEndpoint<"subscription/unsubscribe">
    {
        friend class ::InnerTube;
    protected:
        /**
         * @param params  Supplied by
         * @ref InnertubeObjects::SubscribeButton::onUnsubscribeEndpoints[0]["signalServiceEndpoint"]["actions"][0]["openPopupAction"]["popup"]["confirmDialogRenderer"]["confirmButton"]["buttonRenderer"]["serviceEndpoint"]["unsubscribeEndpoint"] if unsubscribing.
         */
        Unsubscribe(InnertubeContext* context, InnertubeAuthStore* authStore, const QStringList& channelIds,
                    const QString& params);
    };
}
