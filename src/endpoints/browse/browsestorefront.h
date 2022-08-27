#ifndef BROWSESTOREFRONT_H
#define BROWSESTOREFRONT_H
#include <endpoints/base/basebrowseendpoint.h>

namespace InnertubeEndpoints
{
    class BrowseStorefront : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
    private:
        explicit BrowseStorefront(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore) : BaseBrowseEndpoint("FEstorefront", context, easy, authStore) {}
    };
}

#endif // BROWSESTOREFRONT_H
