#pragma once
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    struct AuthorCommentBadge
    {
        QJsonValue authorEndpoint;
        InnertubeString authorText;
        uint backgroundColor{};
        uint foregroundTitleColor{};
        QString iconTooltip;
        QString iconType;

        AuthorCommentBadge() = default;
        explicit AuthorCommentBadge(const QJsonValue& authorCommentBadgeRenderer)
            : authorEndpoint(authorCommentBadgeRenderer["authorEndpoint"]),
              authorText(authorCommentBadgeRenderer["authorText"]),
              backgroundColor(authorCommentBadgeRenderer["color"]["basicColorPaletteData"]["backgroundColor"].toVariant().toUInt()),
              foregroundTitleColor(authorCommentBadgeRenderer["color"]["basicColorPaletteData"]["foregroundTitleColor"].toVariant().toUInt()),
              iconTooltip(authorCommentBadgeRenderer["iconTooltip"].toString()),
              iconType(authorCommentBadgeRenderer["icon"]["iconType"].toString()) {}
    };
}
