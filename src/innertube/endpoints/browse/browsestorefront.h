#ifndef BROWSESTOREFRONT_H
#define BROWSESTOREFRONT_H
#include "innertube/endpoints/base/basebrowseendpoint.h"

namespace InnertubeEndpoints
{
    class BrowseStorefront : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
        BrowseStorefront(InnertubeContext* context, InnertubeAuthStore* authStore) : BaseBrowseEndpoint("FEstorefront", context, authStore) {}
    };
}

#endif // BROWSESTOREFRONT_H
