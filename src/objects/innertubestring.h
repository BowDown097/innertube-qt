#ifndef INNERTUBESTRING_H
#define INNERTUBESTRING_H
#include <QJsonArray>
#include <QJsonObject>
#include <QString>

namespace InnertubeObjects
{
    class InnertubeString
    {
    public:
        QString accessibilityLabel{}, text{};
        InnertubeString() {}
        InnertubeString(const QJsonValue& textVal)
        {
            const QJsonObject& obj = textVal.toObject();
            if (obj.contains("simpleText"))
            {
                text = obj["simpleText"].toString();
            }
            else
            {
                for (auto&& v : obj["runs"].toArray())
                    text += v.toObject()["text"].toString();
            }

            QJsonObject accessibility = obj["accessibility"].toObject();
            if (!accessibility.isEmpty())
                accessibilityLabel = accessibility["accessibilityData"].toObject()["label"].toString();
        }

        bool operator ==(const InnertubeString& s) const { return !text.isEmpty() ? text == s.text : accessibilityLabel == s.accessibilityLabel; }
        bool operator !=(const InnertubeString& s) const { return !text.isEmpty() ? text != s.text : accessibilityLabel != s.accessibilityLabel; }
    };
}

#endif // INNERTUBESTRING_H
