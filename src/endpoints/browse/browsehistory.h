#ifndef BROWSEHISTORY_H
#define BROWSEHISTORY_H
#include <endpoints/base/basebrowseendpoint.h>

namespace InnertubeEndpoints
{
    class BrowseHistory : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
    private:
        explicit BrowseHistory(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore) : BaseBrowseEndpoint("FEhistory", context, easy, authStore) {}
    };
}

#endif // BROWSEHISTORY_H
