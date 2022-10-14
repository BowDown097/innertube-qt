#ifndef BROWSEHOMESHELVES_H
#define BROWSEHOMESHELVES_H
#include "../base/basebrowseendpoint.h"
#include "innertube/objects/video/video.h"

namespace InnertubeEndpoints
{
    class BrowseHomeShelves : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
    public:
        QString continuationToken;
        QVector<InnertubeObjects::InnertubeString> shelves;
        QVector<InnertubeObjects::Video> videos;
    private:
        BrowseHomeShelves(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore, const QString& tokenIn = "");
    };
}

#endif // BROWSEHOMESHELVES_H
