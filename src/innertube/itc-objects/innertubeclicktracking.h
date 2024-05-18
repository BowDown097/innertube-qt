#pragma once
#include <QJsonObject>

struct InnertubeClickTracking
{
    QString clickTrackingParams;
    explicit InnertubeClickTracking(const QString& clickTrackingParams = "") : clickTrackingParams(clickTrackingParams) {}
    QJsonObject toJson() const { return {{ "clickTrackingParams", clickTrackingParams }}; }
};
