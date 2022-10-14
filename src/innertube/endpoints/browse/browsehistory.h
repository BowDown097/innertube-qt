#ifndef BROWSEHISTORY_H
#define BROWSEHISTORY_H
#include "../base/basebrowseendpoint.h"
#include "innertube/objects/video/video.h"

namespace InnertubeEndpoints
{
    class BrowseHistory : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
    public:
        QString continuationToken;
        QVector<InnertubeObjects::Video> videos;
    private:
        BrowseHistory(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore, const QString& tokenIn = "");
    };
}

#endif // BROWSEHISTORY_H
