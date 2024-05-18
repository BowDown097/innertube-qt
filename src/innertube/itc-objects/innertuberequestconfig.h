#pragma once
#include <QJsonObject>

struct InnertubeRequestConfig
{
    bool useSsl;
    explicit InnertubeRequestConfig(bool useSsl = true) : useSsl(useSsl) {}
    QJsonObject toJson() const { return {{ "useSsl", useSsl }}; }
};
