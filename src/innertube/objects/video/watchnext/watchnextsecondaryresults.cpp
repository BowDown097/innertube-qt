#include "watchnextsecondaryresults.h"
#include <QJsonArray>

using namespace Qt::StringLiterals;

namespace InnertubeObjects
{
    WatchNextSecondaryResults::WatchNextSecondaryResults(const QJsonValue& results)
    {
        const QJsonArray resultsArr = results.toArray();
        for (const QJsonValue& result : resultsArr)
        {
            const QJsonObject resultObj = result.toObject();
            QJsonObject::const_iterator resultBegin = resultObj.begin();

            if (resultBegin.key() == "itemSectionRenderer")
            {
                if (resultBegin.value()["sectionIdentifier"_L1].toString() == "sid-wn-chips")
                {
                    const QJsonArray contents = resultBegin.value()["contents"_L1].toArray();
                    for (const QJsonValue& item : contents)
                    {
                        const QJsonObject itemObj = item.toObject();
                        handleItem(itemObj.begin());
                    }
                }
            }
            else if (resultBegin.key() == "relatedChipCloudRenderer")
            {
                relatedChipCloud.emplace(resultBegin.value());
            }
            else
            {
                handleItem(resultBegin);
            }
        }
    }

    void WatchNextSecondaryResults::handleItem(QJsonObject::const_iterator item)
    {
        if (item.key() == "lockupViewModel")
            feed.append(LockupViewModel(item.value()));
        else if (item.key() == "adSlotRenderer")
            feed.append(AdSlot(item.value()));
        else if (item.key() == "continuationItemRenderer")
            feedContinuation = item.value()["continuationEndpoint"_L1]["continuationCommand"_L1]["token"_L1].toString();
    }
}
