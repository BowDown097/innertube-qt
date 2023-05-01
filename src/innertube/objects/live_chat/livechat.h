#ifndef LIVECHAT_H
#define LIVECHAT_H
#include <QJsonValue>

namespace InnertubeObjects
{
    class LiveChat
    {
    public:
        QStringList continuations;
        QString initialDisplayState;

        LiveChat() = default;
        explicit LiveChat(const QJsonValue& liveChatRenderer);
    };
}

#endif // LIVECHAT_H
