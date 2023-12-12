#include "poll.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    Poll::Poll(const QJsonValue& pollRenderer)
        : accessibilityLabel(pollRenderer["accessibilityData"]["accessibilityData"]["label"].toString()),
          totalVotes(pollRenderer["totalVotes"]["simpleText"].toString()),
          type(pollRenderer["type"].toString())
    {
        const QJsonArray choicesJson = pollRenderer["choices"].toArray();
        for (const QJsonValue& choice : choicesJson)
            choices.append(PollChoice(choice));
    }
}
