#ifndef BROWSETRENDING_H
#define BROWSETRENDING_H
#include "../base/basebrowseendpoint.h"

namespace InnertubeEndpoints
{
    class BrowseTrending : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
        BrowseTrending(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore) : BaseBrowseEndpoint("FEtrending", context, easy, authStore) {}
    };
}

#endif // BROWSETRENDING_H
