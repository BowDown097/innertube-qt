#include "unseencount.h"
#include "jsonutil.h"

namespace InnertubeEndpoints
{
    UnseenCount::UnseenCount(const QJsonValue& data)
        // unseenCount can be in a few spots, so a recursive find is used here for simplicity sake
        : unseenCount(JsonUtil::rfind("unseenCount", data).toInt()) {}

    QJsonObject UnseenCount::createBody(const InnertubeContext* context)
    {
        return { { "context", context->toJson() } };
    }
}
