#ifndef EMOJIPICKERCATEGORY_H
#define EMOJIPICKERCATEGORY_H
#include <QJsonValue>

namespace InnertubeObjects
{
    struct EmojiPickerCategory
    {
        QString categoryId;
        QString categoryType;
        QStringList emojiIds;
        QString title;

        EmojiPickerCategory() = default;
        explicit EmojiPickerCategory(const QJsonValue& emojiPickerCategoryRenderer);
    };
}

#endif // EMOJIPICKERCATEGORY_H
