#include "browsechannel.h"
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    BrowseChannel::BrowseChannel(const QString& channelId, InnertubeContext* context, InnertubeAuthStore* authStore, const QString& tokenIn,
                                 const QString& params)
    {
        QJsonObject body = { { "context", context->toJson() } };
        if (tokenIn.isEmpty())
        {
            body.insert("browseId", channelId);
            if (!params.isEmpty()) body.insert("params", params);
        }
        else
        {
            body.insert("continuation", tokenIn);
        }

        QByteArray data = get("browse", context, authStore, body);
        QJsonValue dataObj = QJsonDocument::fromJson(data).object();

        response.contents = dataObj["contents"];
        response.header = InnertubeObjects::ChannelHeader(dataObj["header"]["c4TabbedHeaderRenderer"]);
        response.metadata = InnertubeObjects::ChannelMetadata(dataObj["metadata"]["channelMetadataRenderer"]);
        response.microformat = InnertubeObjects::MicroformatData(dataObj["microformat"]["microformatDataRenderer"]);
    }
}
