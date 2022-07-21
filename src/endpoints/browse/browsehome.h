#ifndef BROWSEHOME_H
#define BROWSEHOME_H
#include <endpoints/base/basebrowseendpoint.h>

namespace InnertubeEndpoints
{
    class BrowseHome : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
    private:
        explicit BrowseHome(InnertubeContext* context, QNetworkAccessManager* manager, InnertubeAuthStore* authStore)
            : BaseBrowseEndpoint("FEwhat_to_watch", context, manager, authStore) {}
    };
}

#endif // BROWSEHOME_H
