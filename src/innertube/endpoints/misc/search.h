#ifndef SEARCH_H
#define SEARCH_H
#include "../base/baseendpoint.h"
#include "innertube/objects/channel/channel.h"
#include "innertube/objects/video/video.h"

namespace InnertubeEndpoints
{
    class Search : public BaseEndpoint
    {
        friend class ::InnerTube;
    public:
        QVector<InnertubeObjects::Channel> channels;
        QString continuationToken;
        long estimatedResults;
        QVector<InnertubeObjects::Video> videos;
    private:
        Search(const QString& query, InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore, const QString& tokenIn = "");
    };
}

#endif // SEARCH_H
