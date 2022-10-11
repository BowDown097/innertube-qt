#ifndef BROWSELIBRARY_H
#define BROWSELIBRARY_H
#include <endpoints/base/basebrowseendpoint.h>

namespace InnertubeEndpoints
{
    class BrowseLibrary : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
    private:
        BrowseLibrary(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore) : BaseBrowseEndpoint("FElibrary", context, easy, authStore) {}
    };
}

#endif // BROWSELIBRARY_H
