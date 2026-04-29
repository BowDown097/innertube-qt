#include "accountslist.h"

namespace InnertubeEndpoints
{
    AccountsList::AccountsList(const QJsonValue& data)
    {
        const QJsonValue channelSwitcherPageRenderer = data["actions"][0]
            ["updateChannelSwitcherPageAction"]["page"]["channelSwitcherPageRenderer"];
        if (!channelSwitcherPageRenderer.isObject())
            throw InnertubeException("[AccountsList] channelSwitcherPageRenderer not found");

        response.page = InnertubeObjects::ChannelSwitcherPage(channelSwitcherPageRenderer);
        response.selectText = data["selectText"]["simpleText"].toString();
    }

    QJsonObject AccountsList::createBody(const InnertubeContext* context)
    {
        return {
            { "callCircumstance", "SWITCHING_USERS_FULL" },
            { "context", context->toJson() },
            { "requestType", "ACCOUNTS_LIST_REQUEST_TYPE_CHANNEL_SWITCHER" }
        };
    }
}