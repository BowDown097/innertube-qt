#ifndef INNERTUBECLICKTRACKING_H
#define INNERTUBECLICKTRACKING_H
#include <QJsonObject>
#include <QString>

class InnertubeClickTracking
{
public:
    QString clickTrackingParams;
    explicit InnertubeClickTracking(const QString& ctp = "") : clickTrackingParams(ctp) {}
    QJsonObject toJson() const { return {{ "clickTrackingParams", clickTrackingParams }}; }
};

#endif // INNERTUBECLICKTRACKING_H
