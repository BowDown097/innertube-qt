#include "unseencount.h"
#include <QJsonArray>
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    UnseenCount::UnseenCount(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore)
    {
        QJsonObject body = { { "context", context->toJson() } };
        QByteArray data;
        get("notification/get_unseen_count", context, authStore, easy, body, data);
        // unseenCount can be in a few spots, so a recursive find is used here for simplicity sake
        unseenCount = rfind("unseenCount", QJsonDocument::fromJson(data).object()).toInt();
    }

    QJsonValue UnseenCount::rfind(const QString& key, const QJsonValue& val)
    {
        if (val.isObject())
        {
            const QJsonObject obj = val.toObject();
            if (obj.contains(key))
                return obj.value(key);

            for (const QJsonValue& v : obj)
            {
                QJsonValue recurse = rfind(key, v);
                if (!recurse.isNull()) return recurse;
            }
        }
        else if (val.isArray())
        {
            const QJsonArray arr = val.toArray();
            for (const QJsonValue& v : arr)
            {
                QJsonValue recurse = rfind(key, v);
                if (!recurse.isNull()) return recurse;
            }
        }

        return QJsonValue();
    }
}
