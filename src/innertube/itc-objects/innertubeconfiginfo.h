#pragma once
#include <QJsonObject>

struct InnertubeConfigInfo
{
    QString appInstallData;
    explicit InnertubeConfigInfo(const QString& appInstallData = "") : appInstallData(appInstallData) {}
    QJsonObject toJson() const { return {{ "appInstallData", appInstallData }}; }
};
