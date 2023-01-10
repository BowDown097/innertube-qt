#ifndef INNERTUBE_JSONUTIL_H
#define INNERTUBE_JSONUTIL_H
#include <QJsonValue>

class JsonUtil
{
public:
    static QJsonValue rfind(const QString& key, const QJsonValue& parent);
};

#endif // INNERTUBE_JSONUTIL_H
