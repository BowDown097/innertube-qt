#pragma once
#include <QJsonValue>

namespace InnertubeObjects
{
    struct BadgeViewModel
    {
        QString badgeStyle;
        QString badgeText;
        QString iconName;

        BadgeViewModel() = default;
        explicit BadgeViewModel(const QJsonValue& badgeViewModel)
            : badgeStyle(badgeViewModel["badgeStyle"].toString()),
              badgeText(badgeViewModel["badgeText"].toString()),
              iconName(badgeViewModel["iconName"].toString()) {}
    };
}
