#ifndef INNERTUBEREQUESTCONFIG_H
#define INNERTUBEREQUESTCONFIG_H
#include <QJsonObject>

class InnertubeRequestConfig
{
public:
    bool useSsl;
    explicit InnertubeRequestConfig(bool useSsl = true) : useSsl(useSsl) {}
    QJsonObject toJson() const { return {{ "useSsl", useSsl }}; }
};

#endif // INNERTUBEREQUESTCONFIG_H
