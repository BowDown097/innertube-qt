#pragma once
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/objects/channel/notificationpreferencebutton.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Change channel notification preferences.
     */
    struct ModifyChannelPreference : BaseEndpoint<"notification/modify_channel_preference">
    {
        QString channelId;
        InnertubeObjects::NotificationPreferenceButton newNotificationButton;

        explicit ModifyChannelPreference(const QJsonValue& data);

        /**
         * @param params  Supplied by @ref InnertubeObjects::MenuServiceItem::serviceEndpoint["modifyChannelNotificationPreferenceEndpoint"]["params"].
         */
        static QJsonObject createBody(const InnertubeContext* context, const QString& params);
    };
}
