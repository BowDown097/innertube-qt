#pragma once
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/responses/misc/accountmenuresponse.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Account menu.
     */
    class AccountMenu : public BaseEndpoint<"account/account_menu">
    {
        friend class ::InnerTube;
    public:
        AccountMenuResponse response;
    protected:
        AccountMenu(const InnertubeContext* context, const InnertubeAuthStore* authStore);
        explicit AccountMenu(const QJsonValue& data);
    private:
        static QJsonObject createBody(const InnertubeContext* context);
    };
}
