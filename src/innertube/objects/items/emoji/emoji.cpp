#include "emoji.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    Emoji::Emoji(const QJsonValue& emojiObj)
        : emojiId(emojiObj["emojiId"].toString()),
          image(emojiObj["image"]["thumbnails"]),
          isCustomEmoji(emojiObj["isCustomEmoji"].toBool()),
          supportsSkinTone(emojiObj["supportsSkinTone"].toBool())
    {
        const QJsonArray searchTermsJson = emojiObj["searchTerms"].toArray();
        for (const QJsonValue& searchTerm : searchTermsJson)
            searchTerms.append(searchTerm.toString());

        const QJsonArray shortcutsJson = emojiObj["shortcuts"].toArray();
        for (const QJsonValue& shortcut : shortcutsJson)
            shortcuts.append(shortcut.toString());
    }
}
