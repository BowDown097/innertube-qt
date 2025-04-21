#pragma once
#include "innertube/endpoints/base/baseendpoint.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Unseen notification count.
     */
    struct UnseenCount : BaseEndpoint<"notification/get_unseen_count">
    {
        int unseenCount;

        explicit UnseenCount(const QJsonValue& data);
        static QJsonObject createBody(const InnertubeContext* context);
    };
}
