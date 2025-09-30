#pragma once
#include <QFont>
#include <QJsonValue>

namespace InnertubeObjects
{
    struct InnertubeRun
    {
        // text properties
        QJsonValue emoji;
        QJsonValue navigationEndpoint;
        QString text;

        // font properties
        bool strikeOut{};
        QFont::Style style = QFont::StyleNormal;
        QFont::Weight weight = QFont::Normal;

        InnertubeRun() = default;
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

        QString toRichText(bool useLinkText) const;

        friend bool operator==(const InnertubeString& lhs, const InnertubeString& rhs)
        { return lhs.text == rhs.text && lhs.accessibilityLabel == rhs.accessibilityLabel; }
        friend bool operator!=(const InnertubeString& lhs, const InnertubeString& rhs) { return !(lhs == rhs); }
    };
}
