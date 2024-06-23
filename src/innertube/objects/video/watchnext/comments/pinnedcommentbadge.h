#pragma once
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    struct PinnedCommentBadge
    {
        uint foregroundTitleColor{};
        QString iconType;
        InnertubeString label;

        PinnedCommentBadge() = default;
        explicit PinnedCommentBadge(const QJsonValue& pinnedCommentBadgeRenderer)
            : foregroundTitleColor(pinnedCommentBadgeRenderer["color"]["basicColorPaletteData"]["foregroundTitleColor"].toVariant().toUInt()),
              iconType(pinnedCommentBadgeRenderer["icon"]["iconType"].toString()),
              label(pinnedCommentBadgeRenderer["label"]) {}
    };
}
