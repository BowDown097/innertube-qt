#pragma once
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/objects/channel/notificationpreferencebutton.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Change channel notification preferences.
     */
    class ModifyChannelPreference : public BaseEndpoint<"notification/modify_channel_preference">
    {
        friend class ::InnerTube;
    public:
        QString channelId;
        InnertubeObjects::NotificationPreferenceButton newNotificationButton;
    protected:
        /**
         * @param params  Supplied by @ref InnertubeObjects::MenuServiceItem::serviceEndpoint["modifyChannelNotificationPreferenceEndpoint"]["params"].
         */
        ModifyChannelPreference(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& params);
    };
}
