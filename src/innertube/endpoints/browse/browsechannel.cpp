#include "browsechannel.h"
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    BrowseChannel::BrowseChannel(const QString& channelId, InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore, const QString& tokenIn, const QString& params)
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

        QByteArray data;
        get("browse", context, authStore, easy, body, data);

        QJsonValue dataObj = QJsonDocument::fromJson(data).object();
        response.header.append(InnertubeObjects::ChannelHeader(dataObj["header"]["c4TabbedHeaderRenderer"]));
    }
}
