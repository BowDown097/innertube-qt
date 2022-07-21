#ifndef BROWSELIBRARY_H
#define BROWSELIBRARY_H
#include <endpoints/base/basebrowseendpoint.h>

namespace InnertubeEndpoints
{
    class BrowseLibrary : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
    private:
        explicit BrowseLibrary(InnertubeContext* context, QNetworkAccessManager* manager, InnertubeAuthStore* authStore)
            : BaseBrowseEndpoint("FElibrary", context, manager, authStore) {}
    };
}

#endif // BROWSELIBRARY_H
