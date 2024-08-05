#pragma once
#include "innertube/objects/images/responsiveimage.h"

namespace InnertubeObjects
{
    struct Emoji
    {
        QString emojiId;
        ResponsiveImage image;
        bool isCustomEmoji{};
        QStringList searchTerms;
        QStringList shortcuts;
        bool supportsSkinTone{};

        Emoji() = default;
        explicit Emoji(const QJsonValue& emojiObj);
    };
}
