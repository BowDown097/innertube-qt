#ifndef BROWSEHOME_H
#define BROWSEHOME_H
#include "../base/basebrowseendpoint.h"
#include "innertube/objects/video/video.h"

namespace InnertubeEndpoints
{
    class BrowseHome : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
    public:
        QString continuationToken;
        QVector<InnertubeObjects::Video> videos;
    private:
        BrowseHome(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore, const QString& tokenIn = "");
    };
}

#endif // BROWSEHOME_H
