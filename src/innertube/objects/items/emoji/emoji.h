#ifndef EMOJI_H
#define EMOJI_H
#include "innertube/objects/responsiveimage.h"

namespace InnertubeObjects
{
    struct Emoji
    {
        QString emojiId;
        ResponsiveImage image;
        bool isCustomEmoji;
        QStringList searchTerms;
        QStringList shortcuts;
        bool supportsSkinTone;

        Emoji() = default;
        explicit Emoji(const QJsonValue& emojiObj);
    };
}

#endif // EMOJI_H
