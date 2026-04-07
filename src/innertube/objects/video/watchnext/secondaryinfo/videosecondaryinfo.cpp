#include "videosecondaryinfo.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    VideoSecondaryInfo::VideoSecondaryInfo(const QJsonValue& secondaryInfoRenderer)
        : attributedDescription(secondaryInfoRenderer["attributedDescription"]),
          defaultExpanded(secondaryInfoRenderer["defaultExpanded"].toBool()),
          descriptionCollapsedLines(secondaryInfoRenderer["descriptionCollapsedLines"].toInt()),
          metadataRowContainer(secondaryInfoRenderer["metadataRowContainer"]["metadataRowContainerRenderer"]),
          owner(secondaryInfoRenderer["owner"]["videoOwnerRenderer"]),
          showLessCommand(secondaryInfoRenderer["showLessCommand"]),
          showLessText(secondaryInfoRenderer["showLessText"]["simpleText"].toString()),
          showMoreCommand(secondaryInfoRenderer["showMoreCommand"]),
          showMoreText(secondaryInfoRenderer["showMoreText"]["simpleText"].toString())
    {
        const QJsonValue subscribeButtonRenderer = secondaryInfoRenderer
            ["subscribeButton"]["subscribeButtonRenderer"];

        if (const QJsonValue dialogCommand = subscribeButtonRenderer["onSubscribeEndpoints"][0]["showDialogCommand"];
            dialogCommand.isObject())
        {
            subscribeButton = SubscribeButtonViewModel(dialogCommand
                ["panelLoadingStrategy"]["inlineContent"]["dialogViewModel"]
                ["customContent"]["listViewModel"]["listItems"][0]["listItemViewModel"]
                ["trailingButtons"]["buttons"][0]["subscribeButtonViewModel"]);
        }
        else
        {
            subscribeButton = SubscribeButton(subscribeButtonRenderer);
        }

        const QJsonArray headerRunsJson = secondaryInfoRenderer["headerRuns"].toArray();
        for (const QJsonValue& headerRun : headerRunsJson)
            headerRuns.append(HeaderRun(headerRun));
    }
}
