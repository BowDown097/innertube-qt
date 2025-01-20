#pragma once
#include <QJsonValue>

namespace InnertubeObjects
{
    struct InnertubeRun
    {
        QJsonValue emoji;
        QJsonValue navigationEndpoint;
        QString text;

        explicit InnertubeRun(const QString& text, const QJsonValue& navigationEndpoint = {}, const QJsonValue& emoji = {})
            : emoji(emoji), navigationEndpoint(navigationEndpoint), text(text) {}
    };

    struct InnertubeString
    {
        QString accessibilityLabel;
        QList<InnertubeRun> runs;
        QString text;

        InnertubeString() = default;
        explicit InnertubeString(const QString& text);
        explicit InnertubeString(const QJsonValue& textVal);

        friend bool operator==(const InnertubeString& lhs, const InnertubeString& rhs)
        { return lhs.text == rhs.text && lhs.accessibilityLabel == rhs.accessibilityLabel; }
        friend bool operator!=(const InnertubeString& lhs, const InnertubeString& rhs) { return !(lhs == rhs); }
    };
}
