#ifndef POLLCHOICE_H
#define POLLCHOICE_H
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    struct PollChoice
    {
        QJsonValue deselectServiceEndpoint;
        QString numVotes;
        QJsonValue selectServiceEndpoint;
        bool selected;
        InnertubeString text;
        QString votePercentage;
        QString votePercentageIfNotSelected;
        QString votePercentageIfSelected;
        double voteRatio;
        double voteRatioIfNotSelected;
        double voteRatioIfSelected;

        explicit PollChoice(const QJsonValue& choice)
            : deselectServiceEndpoint(choice["deselectServiceEndpoint"]),
              numVotes(choice["numVotes"].toString()),
              selectServiceEndpoint(choice["selectServiceEndpoint"]),
              selected(choice["selected"].toBool()),
              text(choice["text"]),
              votePercentage(choice["votePercentage"]["simpleText"].toString()),
              votePercentageIfNotSelected(choice["votePercentageIfNotSelected"]["simpleText"].toString()),
              votePercentageIfSelected(choice["votePercentageIfSelected"]["simpleText"].toString()),
              voteRatio(choice["voteRatio"].toDouble()),
              voteRatioIfNotSelected(choice["voteRatioIfNotSelected"].toDouble()),
              voteRatioIfSelected(choice["voteRatioIfSelected"].toDouble()) {}
    };
}

#endif // POLLCHOICE_H
