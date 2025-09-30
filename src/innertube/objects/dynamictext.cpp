#include "dynamictext.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    // most logic courtesy of https://github.com/Rehike/Rehike
    InnertubeString DynamicText::unattribute() const
    {
        if (content.isEmpty())
            return {};
        if (!commandRuns.isArray() && !styleRuns.isArray())
            return InnertubeString(content);

        using namespace Qt::StringLiterals;
        static const QHash<QLatin1String, QFont::Weight> weightMap = {
            { "FONT_WEIGHT_THIN"_L1, QFont::Thin },
            { "FONT_WEIGHT_EXTRA_LIGHT"_L1, QFont::ExtraLight },
            { "FONT_WEIGHT_LIGHT"_L1, QFont::Light },
            { "FONT_WEIGHT_MEDIUM"_L1, QFont::Medium },
            { "FONT_WEIGHT_SEMI_BOLD"_L1, QFont::DemiBold },
            { "FONT_WEIGHT_BOLD"_L1, QFont::Bold },
            { "FONT_WEIGHT_EXTRA_BOLD"_L1, QFont::ExtraBold },
            { "FONT_WEIGHT_BLACK"_L1, QFont::Black }
        };

        const QJsonArray commandRunsArr = commandRuns.toArray();
        const QJsonArray styleRunsArr = styleRuns.toArray();

        int previousLength{};
        int previousStart{};
        int textLength{};

        InnertubeString out;

        for (const QJsonValue& styleRun : styleRunsArr)
        {
            int length, startIndex;

            if (const QJsonValue indexValue = styleRun["startIndex"]; !indexValue.isUndefined())
                startIndex = indexValue.toInt();
            else
                continue;

            if (const QJsonValue lengthValue = styleRun["length"]; !lengthValue.isUndefined())
                length = lengthValue.toInt();
            else
                length = content.size();

            InnertubeRun run(content.mid(startIndex, length));
            textLength += run.text.size();

            if (auto commandRun = std::ranges::find_if(commandRunsArr, [=](const QJsonValue& run) {
                    return run["length"].toInt() == length && run["startIndex"].toInt() == startIndex;
                }); commandRun != commandRunsArr.end())
            {
                run.navigationEndpoint = (*commandRun)["onTap"_L1]["innertubeCommand"_L1];
            }

            if (!styleRun["strikethrough"].isUndefined())
                run.strikeOut = true;
            if (styleRun["italic"].toBool())
                run.style = QFont::StyleItalic;
            run.weight = weightMap.value(styleRun["weightLabel"].toString(), QFont::Normal);

            if (previousStart + previousLength < startIndex)
            {
                int plainStart = previousStart + previousLength;
                int plainLength = startIndex - plainStart;
                InnertubeRun plainRun(content.mid(plainStart, plainLength));
                textLength += plainRun.text.size();
                out.runs.append(std::move(plainRun));
            }

            out.runs.append(std::move(run));
            previousStart = startIndex;
            previousLength = length;
        }

        return out;
    }
}
