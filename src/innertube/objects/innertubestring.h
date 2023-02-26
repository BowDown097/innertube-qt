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
        InnertubeRun(const QString& text, const QJsonValue& navigationEndpoint = QJsonValue())
            : navigationEndpoint(navigationEndpoint), text(text) {}
    };

    class InnertubeString
    {
    public:
        QString accessibilityLabel;
        QList<InnertubeRun> runs;
        QString text;

        InnertubeString() {}
        explicit InnertubeString(const QString& text);
        explicit InnertubeString(const QJsonValue& textVal);

        bool operator ==(const InnertubeString& s) const { return !text.isEmpty() ? text == s.text : accessibilityLabel == s.accessibilityLabel; }
        bool operator !=(const InnertubeString& s) const { return !text.isEmpty() ? text != s.text : accessibilityLabel != s.accessibilityLabel; }
    };
}

#endif // INNERTUBESTRING_H
