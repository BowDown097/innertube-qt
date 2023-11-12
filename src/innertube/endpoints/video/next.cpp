#include "next.h"
#include "innertube/innertubeexception.h"
#include "innertube/itc-objects/innertubeplaybackcontext.h"
#include "jsonutil.h"
#include <QJsonArray>
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    Next::Next(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& videoId, const QString& tokenIn)
    {
        const QJsonObject body {
            { "autonavState", "STATE_ON" },
            { "captionsRequested", false },
            { "contentCheckOk", false },
            { "context", context->toJson() },
            { "playbackContext", InnertubePlaybackContext().toJson() },
            { "racyCheckOk", false },
            { "videoId", videoId }
        };

        QByteArray data = get(context, authStore, body);
        QJsonValue dataObj = QJsonDocument::fromJson(data).object();

        if (tokenIn.isEmpty())
        {
            QJsonArray watchNextContents = dataObj["contents"]["twoColumnWatchNextResults"]["results"]["results"]["contents"].toArray();
            if (watchNextContents.isEmpty())
                throw InnertubeException("[Next] watchNextResults not found or is empty");

            QJsonValue liveChatRenderer = dataObj["contents"]["twoColumnWatchNextResults"]["conversationBar"]["liveChatRenderer"];
            response.liveChat = liveChatRenderer.isObject()
                ? std::make_optional<InnertubeObjects::LiveChat>(liveChatRenderer) : std::nullopt;

            response.primaryInfo = InnertubeObjects::VideoPrimaryInfo(JsonUtil::rfind("videoPrimaryInfoRenderer", watchNextContents));
            response.secondaryInfo = InnertubeObjects::VideoSecondaryInfo(JsonUtil::rfind("videoSecondaryInfoRenderer", watchNextContents));
            response.videoId = dataObj["currentVideoEndpoint"]["watchEndpoint"]["videoId"].toString();
        }
        // TODO: comments (and thus continuations)
    }
}
