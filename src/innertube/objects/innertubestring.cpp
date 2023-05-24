#include "innertubestring.h"
#include <QJsonArray>

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
        if (textVal["simpleText"].isString())
        {
            const QString simpleText = textVal["simpleText"].toString();
            runs.append(InnertubeRun(simpleText));
            text = simpleText;
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
