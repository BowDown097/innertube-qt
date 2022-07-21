#ifndef BROWSETRENDING_H
#define BROWSETRENDING_H
#include <endpoints/base/basebrowseendpoint.h>

namespace InnertubeEndpoints
{
    class BrowseTrending : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
    private:
        explicit BrowseTrending(InnertubeContext* context, QNetworkAccessManager* manager, InnertubeAuthStore* authStore)
            : BaseBrowseEndpoint("FEtrending", context, manager, authStore) {}
    };
}

#endif // BROWSETRENDING_H
