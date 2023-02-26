#include "innertubestring.h"
#include <QJsonArray>
#include <QJsonObject>

namespace InnertubeObjects
{
    InnertubeString::InnertubeString(const QString& text)
        : accessibilityLabel(text), text(text)
    {
        runs.append(InnertubeRun(text));
    }

    InnertubeString::InnertubeString(const QJsonValue& textVal)
        : accessibilityLabel(textVal["accessibility"]["accessibilityData"]["label"].toString())
    {
        if (textVal.toObject().contains("simpleText"))
        {
            runs.append(InnertubeRun(textVal["simpleText"].toString()));
            text = textVal["simpleText"].toString();
        }
        else
        {
            const QJsonArray runsJson = textVal["runs"].toArray();
            for (const QJsonValue& v : runsJson)
            {
                runs.append(InnertubeRun(v["text"].toString(), v["navigationEndpoint"]));
                text += v["text"].toString();
            }
        }
    }
}
