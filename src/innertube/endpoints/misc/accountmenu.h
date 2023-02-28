#ifndef ACCOUNTMENU_H
#define ACCOUNTMENU_H
#include "innertube/endpoints/base/baseendpoint.h"

namespace InnertubeEndpoints
{
    class AccountMenu : public BaseEndpoint
    {
        friend class ::InnerTube;
        AccountMenu(InnertubeContext* context, InnertubeAuthStore* authStore);
    };
}

#endif // ACCOUNTMENU_H
