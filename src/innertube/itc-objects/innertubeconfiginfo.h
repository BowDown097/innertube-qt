#pragma once
#include <QJsonValue>

struct InnertubeConfigInfo
{
    QString appInstallData;
    explicit InnertubeConfigInfo(const QString& appInstallData = "") : appInstallData(appInstallData) {}
    QJsonObject toJson() const;
};
