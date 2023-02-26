#include "videosecondaryinfo.h"
#include <QJsonObject>

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
        const QJsonObject obj = secondaryInfoRenderer.toObject();

        // attributed description conversion logic courtesy of https://github.com/Rehike/Rehike
        if (obj.contains("attributedDescription"))
        {
            const QJsonObject attrDesc = secondaryInfoRenderer["attributedDescription"].toObject();
            if (!attrDesc.contains("commandRuns"))
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
                const QJsonObject navigationEndpoint = run.navigationEndpoint.toObject();
                if (navigationEndpoint.contains("watchEndpoint") && !navigationEndpoint["watchEndpoint"]["continuePlayback"].toBool())
                {
                    QString fullUrl = "https://www.youtube.com" + navigationEndpoint["commandMetadata"]["webCommandMetadata"]["url"].toString();
                    run.text = fullUrl.mid(0, 37) + "...";
                }
                else if (navigationEndpoint.contains("browseEndpoint"))
                {
                    run.text.replace(run.text.indexOf('/'), 1, "");
                    run.text.replace("\xc2\xa0", "");
                }

                outDescription.accessibilityLabel += run.text;
                outDescription.text += run.text;
            }

            description = outDescription;
        }
        else if (obj.contains("description"))
        {
            description = InnertubeString(secondaryInfoRenderer["description"]);
        }
    }
}
