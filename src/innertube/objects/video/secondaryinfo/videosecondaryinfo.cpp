#include "videosecondaryinfo.h"

namespace InnertubeObjects
{
    VideoSecondaryInfo::VideoSecondaryInfo(const QJsonValue& secondaryInfoRenderer)
        : defaultExpanded(secondaryInfoRenderer["defaultExpanded"].toBool()),
          descriptionCollapsedLines(secondaryInfoRenderer["descriptionCollapsedLines"].toInt()),
          metadataRowContainer(secondaryInfoRenderer["metadataRowContainer"]["metadataRowContainerRenderer"]),
          owner(secondaryInfoRenderer["owner"]["videoOwnerRenderer"]),
          showLessText(secondaryInfoRenderer["showLessText"]["simpleText"].toString()),
          showMoreText(secondaryInfoRenderer["showMoreText"]["simpleText"].toString()),
          subscribeButton(secondaryInfoRenderer["subscribeButton"]["subscribeButtonRenderer"])
    {
        // attributed description conversion logic courtesy of https://github.com/Rehike/Rehike
        if (secondaryInfoRenderer["attributedDescription"].isObject())
        {
            QJsonValue attrDesc = secondaryInfoRenderer["attributedDescription"];
            if (!attrDesc["commandRuns"].isArray())
            {
                description = InnertubeString(attrDesc["content"].toString());
                return;
            }

            QString content = attrDesc["content"].toString();
            InnertubeString outDescription;
            int start = 0;

            const QJsonArray commandRuns = attrDesc["commandRuns"].toArray();
            for (const QJsonValue& commandRun : commandRuns)
            {
                int length = commandRun["length"].toInt();
                int startIndex = commandRun["startIndex"].toInt();

                QString beforeText = content.mid(start, startIndex - start);
                if (!beforeText.isEmpty())
                    outDescription.runs.append(InnertubeRun(beforeText));

                QString linkText = content.mid(startIndex, length);
                outDescription.runs.append(InnertubeRun(linkText, commandRun["onTap"]["innertubeCommand"]));
                start = startIndex + length;
            }

            QString lastText = content.mid(start);
            if (!lastText.isEmpty())
                outDescription.runs.append(InnertubeRun(lastText));

            for (InnertubeObjects::InnertubeRun& run : outDescription.runs)
            {
                if (run.navigationEndpoint["watchEndpoint"].isObject() && !run.navigationEndpoint["watchEndpoint"]["continuePlayback"].toBool())
                {
                    QString fullUrl = "https://www.youtube.com" + run.navigationEndpoint["commandMetadata"]["webCommandMetadata"]["url"].toString();
                    run.text = fullUrl.left(37) + "...";
                }
                else if (run.navigationEndpoint["browseEndpoint"].isObject())
                {
                    run.text.replace(run.text.indexOf('/'), 1, "");
                    run.text.replace("\xc2\xa0", "");
                }

                outDescription.accessibilityLabel += run.text;
                outDescription.text += run.text;
            }

            description = outDescription;
        }
        else if (secondaryInfoRenderer["description"].isObject())
        {
            description = InnertubeString(secondaryInfoRenderer["description"]);
        }
    }
}
