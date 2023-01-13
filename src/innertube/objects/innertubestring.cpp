#include "innertubestring.h"
#include <QJsonArray>
#include <QJsonObject>

namespace InnertubeObjects
{
    InnertubeString::InnertubeString(const QJsonValue& textVal)
        : accessibilityLabel(textVal["accessibility"]["accessibilityData"]["label"].toString())
    {
        if (textVal.toObject().contains("simpleText"))
        {
            text = textVal["simpleText"].toString();
        }
        else
        {
            const QJsonArray runs = textVal["runs"].toArray();
            for (const QJsonValue& v : runs)
                text += v["text"].toString();
        }
    }
}
