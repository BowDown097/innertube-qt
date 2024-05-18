#pragma once
#include "innertube/objects/account_menu/activeaccountheader.h"
#include "innertube/objects/compactlink.h"

namespace InnertubeEndpoints
{
    struct AccountMenuResponse
    {
        InnertubeObjects::ActiveAccountHeader header;
        QList<QList<InnertubeObjects::CompactLink>> sections;
        QString style;
    };
}
