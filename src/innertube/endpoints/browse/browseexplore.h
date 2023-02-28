#ifndef BROWSEEXPLORE_H
#define BROWSEEXPLORE_H
#include "innertube/endpoints/base/basebrowseendpoint.h"

namespace InnertubeEndpoints
{
    class BrowseExplore : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
        BrowseExplore(InnertubeContext* context, InnertubeAuthStore* authStore) : BaseBrowseEndpoint("FEexplore", context, authStore) {}
    };
}

#endif // BROWSEEXPLORE_H
