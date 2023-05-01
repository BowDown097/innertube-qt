#include "livechat.h"
#include <QJsonArray>
#include <QJsonObject>

namespace InnertubeObjects
{
    LiveChat::LiveChat(const QJsonValue& liveChatRenderer) : initialDisplayState(liveChatRenderer["initialDisplayState"].toString())
    {
        const QJsonArray continuationsJson = liveChatRenderer["continuations"].toArray();
        for (const QJsonValue& v : continuationsJson)
        {
            const QJsonObject& o = v.toObject();
            QJsonObject::const_iterator begin = o.begin();
            if (begin == o.end())
                continue;

            const QJsonValue& beginVal = *begin;
            continuations.append(beginVal["continuation"].toString());
        }
    }
}
