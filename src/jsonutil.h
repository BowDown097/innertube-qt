#ifndef INNERTUBE_JSONUTIL_H
#define INNERTUBE_JSONUTIL_H
#include <QJsonValue>

namespace JsonUtil
{
    QJsonValue rfind(const QString& key, const QJsonValue& parent);
}

#endif // INNERTUBE_JSONUTIL_H
