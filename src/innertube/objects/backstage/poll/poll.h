#ifndef POLL_H
#define POLL_H
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

#endif // POLL_H
