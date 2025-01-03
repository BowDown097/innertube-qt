#include "upcomingeventdata.h"

namespace InnertubeObjects
{
    QString UpcomingEventData::formattedEventText() const
    {
        QString fmt = QStringLiteral("%1, %2").arg(
            QLocale::system().dateFormat(QLocale::ShortFormat),
            QLocale::system().timeFormat(QLocale::ShortFormat));

        QString rawUpcomingEventText = upcomingEventText.text;
        return rawUpcomingEventText.replace("DATE_PLACEHOLDER",
            QDateTime::fromSecsSinceEpoch(startTime.toLong()).toString(fmt));
    }
}
