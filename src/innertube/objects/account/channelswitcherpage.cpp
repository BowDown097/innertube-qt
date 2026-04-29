#include "channelswitcherpage.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    ChannelSwitcherPage::ChannelSwitcherPage(const QJsonValue& channelSwitcherPageRenderer)
        : alertMessage(channelSwitcherPageRenderer["alertMessage"]),
          dismissButton(channelSwitcherPageRenderer["dismissButton"]["buttonRenderer"]),
          header(channelSwitcherPageRenderer["header"]["channelSwitcherHeaderRenderer"]),
          noResult(channelSwitcherPageRenderer["noResult"]),
          targetId(channelSwitcherPageRenderer["targetId"].toString())
    {
        const QJsonArray contentsJson = channelSwitcherPageRenderer["contents"].toArray();
        for (const QJsonValue& item : contentsJson)
            if (const QJsonValue accountItem = item["accountItemRenderer"]; accountItem.isObject())
                contents.emplaceBack(accountItem);
    }
}