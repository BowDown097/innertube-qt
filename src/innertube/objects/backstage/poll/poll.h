#pragma once
#include "pollchoice.h"

namespace InnertubeObjects
{
    struct Poll
    {
        QString accessibilityLabel;
        QList<PollChoice> choices;
        QString totalVotes;
        QString type;

        explicit Poll(const QJsonValue& pollRenderer);
    };
}
