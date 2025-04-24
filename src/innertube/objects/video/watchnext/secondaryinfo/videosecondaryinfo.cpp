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
          showMoreText(secondaryInfoRenderer["showMoreText"]["simpleText"].toString()),
          subscribeButton(secondaryInfoRenderer["subscribeButton"]["subscribeButtonRenderer"])
    {
        const QJsonArray headerRunsJson = secondaryInfoRenderer["headerRuns"].toArray();
        for (const QJsonValue& headerRun : headerRunsJson)
            headerRuns.append(HeaderRun(headerRun));
    }
}
