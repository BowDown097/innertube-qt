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
        bool hasSimpleText{};
        if (QString simpleText = textVal["simpleText"].toString(); !simpleText.isEmpty())
        {
            text = simpleText;
            hasSimpleText = true;
        }

        const QJsonArray runsJson = textVal["runs"].toArray();
        for (const QJsonValue& v : runsJson)
        {
            runs.append(InnertubeRun(v["text"].toString(), v["navigationEndpoint"]));
            if (!hasSimpleText)
                text += v["text"].toString();
        }
    }
}
