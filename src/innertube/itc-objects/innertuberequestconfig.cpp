#include "innertuberequestconfig.h"
#include <QJsonObject>

QJsonObject InnertubeRequestConfig::toJson() const
{
    return {
        { "useSsl", useSsl }
    };
}
