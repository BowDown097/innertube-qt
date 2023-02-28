#ifndef BROWSELIBRARY_H
#define BROWSELIBRARY_H
#include "innertube/endpoints/base/basebrowseendpoint.h"

namespace InnertubeEndpoints
{
    class BrowseLibrary : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
        BrowseLibrary(InnertubeContext* context, InnertubeAuthStore* authStore) : BaseBrowseEndpoint("FElibrary", context, authStore) {}
    };
}

#endif // BROWSELIBRARY_H
