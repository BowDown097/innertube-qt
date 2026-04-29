#pragma once
#include "accountitem.h"
#include "channelswitcherheader.h"

namespace InnertubeObjects
{
    struct ChannelSwitcherPage
    {
        InnertubeString alertMessage;
        QList<AccountItem> contents;
        Button dismissButton;
        ChannelSwitcherHeader header;
        InnertubeString noResult;
        QString targetId;

        ChannelSwitcherPage() = default;
        explicit ChannelSwitcherPage(const QJsonValue& channelSwitcherPageRenderer);
    };
}