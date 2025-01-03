#pragma once
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    struct UpcomingEventData
    {
        bool isReminderSet{};
        QString startTime;
        InnertubeString upcomingEventText;

        UpcomingEventData() = default;
        explicit UpcomingEventData(const QJsonValue& upcomingEventData)
            : isReminderSet(upcomingEventData["isReminderSet"].toBool()),
              startTime(upcomingEventData["startTime"].toString()),
              upcomingEventText(upcomingEventData["upcomingEventText"]) {}

        QString formattedEventText() const;
    };
}
