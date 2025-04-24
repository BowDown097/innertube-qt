#include "autoplaydata.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    AutoplayData::AutoplayData(const QJsonValue& autoplay)
        : countDownSecs(autoplay["countDownSecs"].toInt())
    {
        const QJsonArray setsJson = autoplay["sets"].toArray();
        for (const QJsonValue& set : setsJson)
            sets.append(AutoplaySet(set));
    }
}
