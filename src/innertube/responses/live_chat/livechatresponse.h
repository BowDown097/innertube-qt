#ifndef LIVECHATRESPONSE_H
#define LIVECHATRESPONSE_H
#include "innertube/objects/live_chat/invalidationcontinuation.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    struct LiveChatResponse
    {
        QJsonValue actionPanel;
        QJsonArray actions;
        QList<InnertubeObjects::InvalidationContinuation> continuations;
    };
}

#endif // LIVECHATRESPONSE_H
