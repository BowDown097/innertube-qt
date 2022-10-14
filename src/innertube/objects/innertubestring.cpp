#include "innertubestring.h"
#include <QJsonArray>
#include <QJsonObject>

namespace InnertubeObjects
{
    InnertubeString::InnertubeString(const QJsonValue& textVal)
    {
        QJsonObject obj = textVal.toObject();
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
}
