#pragma once
#include <QJsonValue>

struct InnertubeUserConfig
{
    bool lockedSafetyMode;
    explicit InnertubeUserConfig(bool lockedSafetyMode = false) : lockedSafetyMode(lockedSafetyMode) {}
    QJsonValue toJson() const;
};
