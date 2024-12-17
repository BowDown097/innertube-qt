#pragma once
#include <QJsonValue>

namespace InnertubeObjects
{
    struct LottieData
    {
        bool autoplay{};
        bool loop{};
        QString url;

        LottieData() = default;
        explicit LottieData(const QJsonValue& data)
            : autoplay(data["settings"]["autoplay"].toBool()),
              loop(data["settings"]["loop"].toBool()),
              url(data["url"].toString()) {}
    };
}
