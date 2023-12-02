#ifndef INNERTUBECONFIGINFO_H
#define INNERTUBECONFIGINFO_H
#include <QJsonObject>

struct InnertubeConfigInfo
{
    QString appInstallData;
    explicit InnertubeConfigInfo(const QString& appInstallData = "") : appInstallData(appInstallData) {}
    QJsonObject toJson() const { return {{ "appInstallData", appInstallData }}; }
};

#endif // INNERTUBECONFIGINFO_H
