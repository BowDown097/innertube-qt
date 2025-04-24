#pragma once
#include <QJsonValue>

namespace InnertubeObjects
{
    struct AutoplaySet
    {
        QJsonValue autoplayVideo;
        QString mode;

        AutoplaySet() = default;
        explicit AutoplaySet(const QJsonValue& set)
            : autoplayVideo(set["autoplayVideo"]), mode(set["mode"].toString()) {}
    };

    struct AutoplayData
    {
        int countDownSecs{};
        QList<AutoplaySet> sets;

        AutoplayData() = default;
        explicit AutoplayData(const QJsonValue& autoplay);
    };
}
