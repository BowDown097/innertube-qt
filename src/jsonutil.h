#pragma once
#include <QJsonValue>

namespace JsonUtil
{
    QString getFirstKey(const QJsonValue& value);
    QJsonValue rfind(const QString& key, const QJsonValue& parent);
}
