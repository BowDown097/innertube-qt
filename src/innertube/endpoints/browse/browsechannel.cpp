#include "browsechannel.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    BrowseChannel::BrowseChannel(const QJsonValue& data)
    {
        if (const QJsonValue contents = data["contents"]; contents.isObject())
        {
            response.contents = data["contents"];

            response.metadata = InnertubeObjects::ChannelMetadata(data["metadata"]["channelMetadataRenderer"]);
            response.microformat = InnertubeObjects::MicroformatData(data["microformat"]["microformatDataRenderer"]);

            if (const QJsonValue c4Header = data["header"]["c4TabbedHeaderRenderer"]; c4Header.isObject())
                response.header = InnertubeObjects::ChannelC4Header(c4Header);
            else if (const QJsonValue pageHeader = data["header"]["pageHeaderRenderer"]; pageHeader.isObject())
                response.header = InnertubeObjects::ChannelPageHeader(pageHeader["content"]["pageHeaderViewModel"]);

            const QJsonArray mutations = data["frameworkUpdates"]["entityBatchUpdate"]["mutations"].toArray();
            for (const QJsonValue& mutation : mutations)
                response.mutations.append(InnertubeObjects::EntityMutation(mutation));
        }
        else if (const QJsonValue actions = data["onResponseReceivedActions"]; actions.isArray())
        {
            if (const QJsonValue continueAction = actions[0]["appendContinuationItemsAction"]; continueAction.isObject())
            {
                response.contents = continueAction["continuationItems"];
            }
        }
        // the community tab's response erroneously calls it onResponseReceivedEndpoints
        else if (const QJsonValue endpoints = data["onResponseReceivedEndpoints"]; endpoints.isArray())
        {
            if (const QJsonValue continueAction = endpoints[0]["appendContinuationItemsAction"]; continueAction.isObject())
            {
                response.contents = continueAction["continuationItems"];
            }
        }
    }

    QJsonObject BrowseChannel::createBody(
        const InnertubeContext* context, const QString& channelId,
        const QString& continuationToken, const QString& params)
    {
        return _createBody(context, channelId, continuationToken, "", params);
    }
}
