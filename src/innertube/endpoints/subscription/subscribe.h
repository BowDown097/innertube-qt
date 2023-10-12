#ifndef SUBSCRIBE_H
#define SUBSCRIBE_H
#include "innertube/endpoints/base/baseendpoint.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Subscribe or unsubscribe to/from one or multiple channels.
     */
    class Subscribe : public BaseEndpoint
    {
        friend class ::InnerTube;
    protected:
        /**
         * @param params  Supplied by
         * @ref InnertubeObjects::SubscribeButton::onSubscribeEndpoints[0]["subscribeEndpoint"]["params"] if subscribing and
         * @ref InnertubeObjects::SubscribeButton::onUnsubscribeEndpoints[0]["signalServiceEndpoint"]["actions"][0]["openPopupAction"]["popup"]["confirmDialogRenderer"]["confirmButton"]["buttonRenderer"]["serviceEndpoint"]["unsubscribeEndpoint"] if unsubscribing.
         */
        Subscribe(const QStringList& channelIds, const QString& params, bool subscribing, InnertubeContext* context, InnertubeAuthStore* authStore);
    };
}

#endif // SUBSCRIBE_H
