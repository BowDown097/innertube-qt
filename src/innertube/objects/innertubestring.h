#ifndef INNERTUBESTRING_H
#define INNERTUBESTRING_H
#include <QJsonValue>
#include <QString>

namespace InnertubeObjects
{
    struct InnertubeRun
    {
        QJsonValue navigationEndpoint;
        QString text;
        explicit InnertubeRun(const QString& text, const QJsonValue& navigationEndpoint = QJsonValue())
            : navigationEndpoint(navigationEndpoint), text(text) {}
    };

    class InnertubeString
    {
    public:
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

#endif // INNERTUBESTRING_H
