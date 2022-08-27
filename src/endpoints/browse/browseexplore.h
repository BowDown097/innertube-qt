#ifndef BROWSEEXPLORE_H
#define BROWSEEXPLORE_H
#include <endpoints/base/basebrowseendpoint.h>

namespace InnertubeEndpoints
{
    class BrowseExplore : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
    private:
        explicit BrowseExplore(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore) : BaseBrowseEndpoint("FEexplore", context, easy, authStore) {}
    };
}

#endif // BROWSEEXPLORE_H
