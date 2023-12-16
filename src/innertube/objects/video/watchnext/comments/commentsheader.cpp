#include "commentsheader.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    CommentsHeader::CommentsHeader(const QJsonValue& commentsHeaderRenderer)
        : commentSimplebox(commentsHeaderRenderer["createRenderer"]["commentSimpleboxRenderer"]),
          commentsCount(commentsHeaderRenderer["commentsCount"]),
          countText(commentsHeaderRenderer["countText"]),
          showSeparator(commentsHeaderRenderer["showSeparator"].toBool()),
          sortMenu(commentsHeaderRenderer["sortMenu"]["sortFilterSubMenuRenderer"]),
          titleText(commentsHeaderRenderer["titleText"]),
          unicodeEmojisUrl(commentsHeaderRenderer["unicodeEmojisUrl"].toString())
    {
        const QJsonArray customEmojisJson = commentsHeaderRenderer["customEmojis"].toArray();
        for (const QJsonValue& customEmoji : customEmojisJson)
            customEmojis.append(Emoji(customEmoji));
    }
}
