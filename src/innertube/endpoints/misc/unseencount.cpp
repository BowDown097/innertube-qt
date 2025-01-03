#include "unseencount.h"
#include "jsonutil.h"

namespace InnertubeEndpoints
{
    UnseenCount::UnseenCount(const InnertubeContext* context, const InnertubeAuthStore* authStore)
    {
        const QJsonValue data = get(context, authStore, QJsonObject { { "context", context->toJson() } });
        // unseenCount can be in a few spots, so a recursive find is used here for simplicity sake
        unseenCount = JsonUtil::rfind("unseenCount", data).toInt();
    }
}
