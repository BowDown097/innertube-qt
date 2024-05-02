#include "browsechannel.h"
#include <QJsonArray>
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    BrowseChannel::BrowseChannel(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& channelId,
                                 const QString& tokenIn, const QString& params)
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

        QByteArray data = get(context, authStore, body);
        QJsonValue dataObj = QJsonDocument::fromJson(data).object();

        response.contents = dataObj["contents"];
        response.header = InnertubeObjects::ChannelHeader(dataObj["header"]["pageHeaderRenderer"]["content"]
                                                                 ["pageHeaderViewModel"]);
        response.metadata = InnertubeObjects::ChannelMetadata(dataObj["metadata"]["channelMetadataRenderer"]);
        response.microformat = InnertubeObjects::MicroformatData(dataObj["microformat"]["microformatDataRenderer"]);

        const QJsonArray mutations = dataObj["frameworkUpdates"]["entityBatchUpdate"]["mutations"].toArray();
        for (const QJsonValue& mutation : mutations)
            response.mutations.append(InnertubeObjects::EntityMutation(mutation));
    }
}
