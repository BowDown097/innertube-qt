#ifndef MODIFYCHANNELPREFERENCE_H
#define MODIFYCHANNELPREFERENCE_H
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/objects/channel/notificationpreferencebutton.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Change channel notification preferences.
     */
    class ModifyChannelPreference : public BaseEndpoint
    {
        friend class ::InnerTube;
    public:
        QString channelId;
        InnertubeObjects::NotificationPreferenceButton newNotificationButton;
    protected:
        /**
         * @param params  Supplied by @ref InnertubeObjects::MenuServiceItem::serviceEndpoint["modifyChannelNotificationPreferenceEndpoint"]["params"].
         */
        ModifyChannelPreference(const QString& params, InnertubeContext* context, InnertubeAuthStore* authStore);
    };
}

#endif // MODIFYCHANNELPREFERENCE_H
