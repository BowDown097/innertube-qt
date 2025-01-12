#pragma once
#include "quizchoice.h"

namespace InnertubeObjects
{
    struct Quiz
    {
        QString accessibilityLabel;
        QList<QuizChoice> choices;
        InnertubeString correctVotedText;
        bool disableChangingQuizAnswer{};
        bool enableAnimation{};
        InnertubeString explanationCollapseText;
        InnertubeString explanationExpandText;
        InnertubeString explanationHeaderText;
        InnertubeString totalVotes;
        QString type;
        InnertubeString votedText;

        explicit Quiz(const QJsonValue& quizRenderer);
    };
}
