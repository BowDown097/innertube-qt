#ifndef ACCOUNTMENURESPONSE_H
#define ACCOUNTMENURESPONSE_H
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

#endif // ACCOUNTMENURESPONSE_H
