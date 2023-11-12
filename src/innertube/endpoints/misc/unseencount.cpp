#include "unseencount.h"
#include "jsonutil.h"
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    UnseenCount::UnseenCount(InnertubeContext* context, InnertubeAuthStore* authStore)
    {
        const QJsonObject body = { { "context", context->toJson() } };
        QByteArray data = get(context, authStore, body);
        // unseenCount can be in a few spots, so a recursive find is used here for simplicity sake
        unseenCount = JsonUtil::rfind("unseenCount", QJsonDocument::fromJson(data).object()).toInt();
    }
}
