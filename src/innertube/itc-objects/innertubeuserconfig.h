#ifndef INNERTUBEUSERCONFIG_H
#define INNERTUBEUSERCONFIG_H
#include <QJsonObject>

struct InnertubeUserConfig
{
    bool lockedSafetyMode;
    explicit InnertubeUserConfig(bool lockedSafetyMode = false) : lockedSafetyMode(lockedSafetyMode) {}
    QJsonObject toJson() const { return {{ "lockedSafetyMode", lockedSafetyMode }}; }
};

#endif // INNERTUBEUSERCONFIG_H
