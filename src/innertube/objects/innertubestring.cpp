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
            const QJsonArray runs = obj["runs"].toArray();
            text = std::accumulate(runs.cbegin(), runs.cend(), QString(), [](const QString& result, const QJsonValue& v) {
                return result + v["text"].toString();
            });
        }

        QJsonObject accessibility = obj["accessibility"].toObject();
        if (!accessibility.isEmpty())
            accessibilityLabel = accessibility["accessibilityData"].toObject()["label"].toString();
    }
}
