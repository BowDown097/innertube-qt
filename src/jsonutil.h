#ifndef INNERTUBE_JSONUTIL_H
#define INNERTUBE_JSONUTIL_H
#include <QJsonValue>

struct JsonUtil
{
    static QJsonValue rfind(const QString& key, const QJsonValue& parent);
};

#endif // INNERTUBE_JSONUTIL_H
