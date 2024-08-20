#pragma once
#include "innertube/endpoints/base/basebrowseendpoint.h"
#include "innertube/responses/browse/channelresponse.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Channel info.
     * @details Used on the channel page - youtube.com/c/XXX, youtube.com/channel/XXX, etc.
     */
    class BrowseChannel : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
    public:
        ChannelResponse response;
    protected:
        /**
         * @param tokenIn  Continuation token.
         * @param params  Supplied by response.contents["twoColumnBrowseResultsRenderer"]["tabs"][INDEX]["tabRenderer"]["endpoint"]["browseEndpoint"]["params"]
         * where INDEX is the current tab index.
         */
        BrowseChannel(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& channelId,
                      const QString& tokenIn = "", const QString& params = "");
    };
}
