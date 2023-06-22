#ifndef ACCOUNTMENU_H
#define ACCOUNTMENU_H
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/responses/misc/accountmenuresponse.h"

namespace InnertubeEndpoints
{
    class AccountMenu : public BaseEndpoint
    {
        friend class ::InnerTube;
    public:
        AccountMenuResponse response;
    private:
        AccountMenu(InnertubeContext* context, InnertubeAuthStore* authStore);
    };
}

#endif // ACCOUNTMENU_H
