#pragma once
#include "innertube/endpoints/base/basebrowseendpoint.h"
#include "innertube/responses/browse/channelresponse.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Channel info.
     * @details Used on the channel page - youtube.com/c/XXX, youtube.com/channel/XXX, etc.
     */
    struct BrowseChannel : BaseBrowseEndpoint
    {
        ChannelResponse response;

        explicit BrowseChannel(const QJsonValue& data);

        /**
         * @param params  Supplied by response.contents["twoColumnBrowseResultsRenderer"]["tabs"][INDEX]["tabRenderer"]["endpoint"]["browseEndpoint"]["params"]
         * where INDEX is the current tab index.
         */
        static QJsonObject createBody(
            const InnertubeContext* context, const QString& channelId,
            const QString& continuationToken = "", const QString& params = "");
    };
}
