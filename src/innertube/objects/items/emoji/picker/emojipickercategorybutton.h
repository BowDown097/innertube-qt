#ifndef EMOJIPICKERCATEGORYBUTTON_H
#define EMOJIPICKERCATEGORYBUTTON_H
#include <QJsonValue>

namespace InnertubeObjects
{
    struct EmojiPickerCategoryButton
    {
        QString accessibilityLabel;
        QString categoryId;
        QString iconType;
        QString tooltip;

        EmojiPickerCategoryButton() = default;
        explicit EmojiPickerCategoryButton(const QJsonValue& emojiPickerCategoryButtonRenderer)
            : accessibilityLabel(emojiPickerCategoryButtonRenderer["accessibility"]["accessibilityData"]["label"].toString()),
              categoryId(emojiPickerCategoryButtonRenderer["categoryId"].toString()),
              iconType(emojiPickerCategoryButtonRenderer["icon"]["iconType"].toString()),
              tooltip(emojiPickerCategoryButtonRenderer["tooltip"].toString()) {}
    };
}

#endif // EMOJIPICKERCATEGORYBUTTON_H
