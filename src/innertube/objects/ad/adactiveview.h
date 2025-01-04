#pragma once
#include <QJsonArray>

namespace InnertubeObjects
{
    struct RegexUriMacroValidator
    {
        bool emptyMap{};

        RegexUriMacroValidator() = default;
        explicit RegexUriMacroValidator(const QJsonValue& regexUriMacroValidator)
            : emptyMap(regexUriMacroValidator["emptyMap"].toBool()) {}
    };

    struct AdActiveView
    {
        QJsonArray endOfSessionCommands;
        RegexUriMacroValidator regexUriMacroValidator;
        QJsonArray viewableCommands;

        AdActiveView() = default;
        explicit AdActiveView(const QJsonValue& activeView)
            : endOfSessionCommands(activeView["endOfSessionCommands"].toArray()),
            regexUriMacroValidator(activeView["regexUriMacroValidator"]),
            viewableCommands(activeView["viewableCommands"].toArray()) {}
    };
}
