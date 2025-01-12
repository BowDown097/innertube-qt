#pragma once
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    struct QuizChoice
    {
        QJsonValue deselectServiceEndpoint;
        InnertubeString explanation;
        bool isCorrect{};
        bool isSelected{};
        QJsonValue selectServiceEndpoint;
        InnertubeString text;

        QuizChoice() = default;
        explicit QuizChoice(const QJsonValue& choice)
            : deselectServiceEndpoint(choice["deselectServiceEndpoint"]),
              explanation(choice["explanation"]),
              isCorrect(choice["isCorrect"].toBool()),
              isSelected(choice["isSelected"].toBool()),
              selectServiceEndpoint(choice["selectServiceEndpoint"]),
              text(choice["text"]) {}
    };
}
