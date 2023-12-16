#include "emojipicker.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    EmojiPicker::EmojiPicker(const QJsonValue& emojiPickerRenderer)
        : clearSearchLabel(emojiPickerRenderer["clearSearchLabel"].toString()),
          id(emojiPickerRenderer["id"].toString()),
          pickSkinToneText(emojiPickerRenderer["pickSkinToneText"]),
          searchNoResultsText(emojiPickerRenderer["searchNoResultsText"]),
          searchPlaceholderText(emojiPickerRenderer["searchPlaceholderText"]),
          skinToneDarkLabel(emojiPickerRenderer["skinToneDarkLabel"].toString()),
          skinToneGenericLabel(emojiPickerRenderer["skinToneGenericLabel"].toString()),
          skinToneLightLabel(emojiPickerRenderer["skinToneLightLabel"].toString()),
          skinToneMediumDarkLabel(emojiPickerRenderer["skinToneMediumDarkLabel"].toString()),
          skinToneMediumLabel(emojiPickerRenderer["skinToneMediumLabel"].toString()),
          skinToneMediumLightLabel(emojiPickerRenderer["skinToneMediumLightLabel"].toString())
    {
        const QJsonArray categoriesJson = emojiPickerRenderer["categories"].toArray();
        for (const QJsonValue& category : categoriesJson)
            categories.append(EmojiPickerCategory(category["emojiPickerCategoryRenderer"]));

        const QJsonArray categoryButtonsJson = emojiPickerRenderer["categoryButtons"].toArray();
        for (const QJsonValue& categoryButton : categoryButtonsJson)
            categoryButtons.append(EmojiPickerCategoryButton(categoryButton["emojiPickerCategoryButtonRenderer"]));
    }
}
