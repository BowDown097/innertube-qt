#pragma once
#include "emojipickercategory.h"
#include "emojipickercategorybutton.h"
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    struct EmojiPicker
    {
        QList<EmojiPickerCategory> categories;
        QList<EmojiPickerCategoryButton> categoryButtons;
        QString clearSearchLabel;
        QString id;
        InnertubeString pickSkinToneText;
        InnertubeString searchNoResultsText;
        InnertubeString searchPlaceholderText;
        QString skinToneDarkLabel;
        QString skinToneGenericLabel;
        QString skinToneLightLabel;
        QString skinToneMediumDarkLabel;
        QString skinToneMediumLabel;
        QString skinToneMediumLightLabel;

        EmojiPicker() = default;
        explicit EmojiPicker(const QJsonValue& emojiPickerRenderer);
    };
}
