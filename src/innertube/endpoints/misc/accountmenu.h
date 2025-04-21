#pragma once
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/responses/misc/accountmenuresponse.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Account menu.
     */
    struct AccountMenu : BaseEndpoint<"account/account_menu">
    {
        AccountMenuResponse response;

        explicit AccountMenu(const QJsonValue& data);
        static QJsonObject createBody(const InnertubeContext* context);
    };
}
