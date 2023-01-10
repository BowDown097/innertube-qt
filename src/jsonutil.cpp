#include "jsonutil.h"
#include <QJsonArray>
#include <QJsonObject>

QJsonValue JsonUtil::rfind(const QString& key, const QJsonValue& parent)
{
    if (parent.isObject())
    {
        const QJsonObject obj = parent.toObject();
        if (obj.contains(key))
            return obj.value(key);

        for (const QJsonValue& v : obj)
        {
            QJsonValue recurse = rfind(key, v);
            if (!recurse.isNull()) return recurse;
        }
    }
    else if (parent.isArray())
    {
        const QJsonArray arr = parent.toArray();
        for (const QJsonValue& v : arr)
        {
            QJsonValue recurse = rfind(key, v);
            if (!recurse.isNull()) return recurse;
        }
    }

    return QJsonValue();
}
