#ifndef ACCOUNTMENU_H
#define ACCOUNTMENU_H
#include "../base/baseendpoint.h"

namespace InnertubeEndpoints
{
    class AccountMenu : public BaseEndpoint
    {
        friend class ::InnerTube;
        AccountMenu(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore);
    };
}

#endif // ACCOUNTMENU_H
