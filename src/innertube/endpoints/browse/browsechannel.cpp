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
        response.metadata = InnertubeObjects::ChannelMetadata(dataObj["metadata"]["channelMetadataRenderer"]);
        response.microformat = InnertubeObjects::MicroformatData(dataObj["microformat"]["microformatDataRenderer"]);

        if (QJsonValue c4Header = dataObj["header"]["c4TabbedHeaderRenderer"]; c4Header.isObject())
            response.header = InnertubeObjects::ChannelC4Header(c4Header);
        else if (QJsonValue pageHeader = dataObj["header"]["pageHeaderRenderer"]; pageHeader.isObject())
            response.header = InnertubeObjects::ChannelPageHeader(pageHeader["content"]["pageHeaderViewModel"]);

        const QJsonArray mutations = dataObj["frameworkUpdates"]["entityBatchUpdate"]["mutations"].toArray();
        for (const QJsonValue& mutation : mutations)
            response.mutations.append(InnertubeObjects::EntityMutation(mutation));
    }
}
