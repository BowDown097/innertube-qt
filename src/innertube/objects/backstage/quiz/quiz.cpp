#include "quiz.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    Quiz::Quiz(const QJsonValue& quizRenderer)
        : accessibilityLabel(quizRenderer["accessibilityData"]["accessibilityData"]["label"].toString()),
          correctVotedText(quizRenderer["correctVotedText"]),
          disableChangingQuizAnswer(quizRenderer["disableChangingQuizAnswer"].toBool()),
          enableAnimation(quizRenderer["enableAnimation"].toBool()),
          explanationCollapseText(quizRenderer["explanationCollapseText"]),
          explanationExpandText(quizRenderer["explanationExpandText"]),
          explanationHeaderText(quizRenderer["explanationHeaderText"]),
          totalVotes(quizRenderer["totalVotes"]),
          type(quizRenderer["type"].toString()),
          votedText(quizRenderer["votedText"])
    {
        const QJsonArray choicesJson = quizRenderer["choices"].toArray();
        for (const QJsonValue& choice : choicesJson)
            choices.append(QuizChoice(choice));
    }
}
