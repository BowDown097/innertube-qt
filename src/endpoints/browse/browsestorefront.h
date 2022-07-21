#ifndef BROWSESTOREFRONT_H
#define BROWSESTOREFRONT_H
#include <endpoints/base/basebrowseendpoint.h>

namespace InnertubeEndpoints
{
    class BrowseStorefront : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
    private:
        explicit BrowseStorefront(InnertubeContext* context, QNetworkAccessManager* manager, InnertubeAuthStore* authStore)
            : BaseBrowseEndpoint("FEstorefront", context, manager, authStore) {}
    };
}

#endif // BROWSESTOREFRONT_H
