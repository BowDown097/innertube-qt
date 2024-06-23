#pragma once
#include <QJsonValue>

namespace InnertubeObjects
{
    struct LiveChat
    {
        QStringList continuations;
        QString initialDisplayState;
        bool isReplay{};

        LiveChat() = default;
        explicit LiveChat(const QJsonValue& liveChatRenderer);
    };
}
