#include "emojipickercategory.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    EmojiPickerCategory::EmojiPickerCategory(const QJsonValue& emojiPickerCategoryRenderer)
        : categoryId(emojiPickerCategoryRenderer["categoryId"].toString()),
          categoryType(emojiPickerCategoryRenderer["categoryType"].toString()),
          title(emojiPickerCategoryRenderer["title"]["simpleText"].toString())
    {
        const QJsonArray emojiIdsJson = emojiPickerCategoryRenderer["emojiIds"].toArray();
        for (const QJsonValue& emojiId : emojiIdsJson)
            emojiIds.append(emojiId.toString());
    }
}
