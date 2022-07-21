#ifndef BROWSEEXPLORE_H
#define BROWSEEXPLORE_H
#include <endpoints/base/basebrowseendpoint.h>

namespace InnertubeEndpoints
{
    class BrowseExplore : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
    private:
        explicit BrowseExplore(InnertubeContext* context, QNetworkAccessManager* manager, InnertubeAuthStore* authStore)
            : BaseBrowseEndpoint("FEexplore", context, manager, authStore) {}
    };
}

#endif // BROWSEEXPLORE_H
