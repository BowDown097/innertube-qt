#ifndef INNERTUBECONFIGINFO_H
#define INNERTUBECONFIGINFO_H
#include <QJsonObject>
#include <QString>

class InnertubeConfigInfo
{
public:
    QString appInstallData;
    explicit InnertubeConfigInfo(const QString& appInstallData = "") : appInstallData(appInstallData) {}
    QJsonObject toJson() const { return {{ "appInstallData", appInstallData }}; }
};

#endif // INNERTUBECONFIGINFO_H
