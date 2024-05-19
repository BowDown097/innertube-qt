#include "innertuberequestconfig.h"
#include <QJsonObject>

QJsonValue InnertubeRequestConfig::toJson() const
{
    return QJsonObject {
        { "useSsl", useSsl }
    };
}
