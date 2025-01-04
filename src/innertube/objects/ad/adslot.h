#pragma once
#include "adslotmetadata.h"
#include "infeedadlayout.h"

namespace InnertubeObjects
{
    struct AdFulfillmentContent
    {
        InFeedAdLayout fulfilledLayout;

        AdFulfillmentContent() = default;
        explicit AdFulfillmentContent(const QJsonValue& fulfillmentContent)
            : fulfilledLayout(fulfillmentContent["fulfilledLayout"]["inFeedAdLayoutRenderer"]) {}
    };

    struct AdSlot
    {
        AdSlotMetadata adSlotMetadata;
        bool enablePacfLoggingWeb{};
        AdFulfillmentContent fulfillmentContent;

        AdSlot() = default;
        explicit AdSlot(const QJsonValue& adSlotRenderer)
            : adSlotMetadata(adSlotRenderer["adSlotMetadata"]),
              enablePacfLoggingWeb(adSlotRenderer["enablePacfLoggingWeb"].toBool()),
              fulfillmentContent(adSlotRenderer["fulfillmentContent"]) {}
    };
}
