#ifndef INNERTUBECLICKTRACKING_H
#define INNERTUBECLICKTRACKING_H
#include <QJsonObject>

struct InnertubeClickTracking
{
    QString clickTrackingParams;
    explicit InnertubeClickTracking(const QString& clickTrackingParams = "") : clickTrackingParams(clickTrackingParams) {}
    QJsonObject toJson() const { return {{ "clickTrackingParams", clickTrackingParams }}; }
};

#endif // INNERTUBECLICKTRACKING_H
