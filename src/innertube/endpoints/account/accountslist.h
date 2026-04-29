#pragma once
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/responses/account/accountslistresponse.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Accounts list.
     */
    struct AccountsList : BaseEndpoint<"account/accounts_list">
    {
        AccountsListResponse response;

        explicit AccountsList(const QJsonValue& data);
        static QJsonObject createBody(const InnertubeContext* context);
    };
}