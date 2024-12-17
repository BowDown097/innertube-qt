#pragma once
#include <QJsonValue>

struct InnertubeClickTracking
{
    QString clickTrackingParams;
    explicit InnertubeClickTracking(const QString& clickTrackingParams = "") : clickTrackingParams(clickTrackingParams) {}
    QJsonObject toJson() const;
};
