#pragma once
#include "innertube/endpoints/base/baseendpoint.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Unseen notification count.
     */
    class UnseenCount : public BaseEndpoint<"notification/get_unseen_count">
    {
        friend class ::InnerTube;
    public:
        int unseenCount;
    protected:
        UnseenCount(const InnertubeContext* context, const InnertubeAuthStore* authStore);
    };
}
