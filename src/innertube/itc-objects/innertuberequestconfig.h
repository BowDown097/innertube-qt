#pragma once
#include <QJsonValue>

struct InnertubeRequestConfig
{
    bool useSsl;
    explicit InnertubeRequestConfig(bool useSsl = true) : useSsl(useSsl) {}
    QJsonValue toJson() const;
};
