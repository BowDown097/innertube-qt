#ifndef INNERTUBESTRING_H
#define INNERTUBESTRING_H
#include <QJsonValue>
#include <QString>

namespace InnertubeObjects
{
    class InnertubeString
    {
    public:
        QString accessibilityLabel{}, text{};
        InnertubeString() {}
        explicit InnertubeString(const QJsonValue& textVal);

        bool operator ==(const InnertubeString& s) const { return !text.isEmpty() ? text == s.text : accessibilityLabel == s.accessibilityLabel; }
        bool operator !=(const InnertubeString& s) const { return !text.isEmpty() ? text != s.text : accessibilityLabel != s.accessibilityLabel; }
    };
}

#endif // INNERTUBESTRING_H
