#pragma once
#include <QJsonValue>

namespace JsonUtil
{
    void deepMerge(QJsonObject& target, const QJsonObject& source);
    QString getFirstKey(const QJsonValue& value);
    QJsonValue rfind(const QString& key, const QJsonValue& parent);
}
