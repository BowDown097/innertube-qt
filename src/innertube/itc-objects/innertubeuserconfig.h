#pragma once
#include <QJsonObject>

struct InnertubeUserConfig
{
    bool lockedSafetyMode;
    explicit InnertubeUserConfig(bool lockedSafetyMode = false) : lockedSafetyMode(lockedSafetyMode) {}
    QJsonObject toJson() const { return {{ "lockedSafetyMode", lockedSafetyMode }}; }
};
