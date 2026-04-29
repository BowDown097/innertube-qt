#include "accountitem.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    AccountItem::AccountItem(const QJsonValue& accountItemRenderer)
        : accountByline(accountItemRenderer["accountByline"]),
          accountName(accountItemRenderer["accountName"]),
          accountPhoto(accountItemRenderer["accountPhoto"]["thumbnails"]),
          channelHandle(accountItemRenderer["channelHandle"]),
          hasChannel(accountItemRenderer["hasChannel"].toBool()),
          isDisabled(accountItemRenderer["isDisabled"].toBool()),
          isSelected(accountItemRenderer["isSelected"].toBool()),
          mobileBanner(accountItemRenderer["mobileBanner"]["thumbnails"]),
          serviceEndpoint(accountItemRenderer["serviceEndpoint"])
    {
        const QJsonArray directiveInts = accountItemRenderer["accountLogDirectiveInts"].toArray();
        for (const QJsonValue& directiveInt : directiveInts)
            accountLogDirectiveInts.append(directiveInt.toInt());
    }

    QString AccountItem::channelOrPageId() const
    {
        const QJsonArray supportedTokens = serviceEndpoint
            ["selectActiveIdentityEndpoint"]["supportedTokens"].toArray();

        for (const QJsonValue& token : supportedTokens)
        {
            // pageIdToken should only exist, and if it does, always be first, for brand accounts
            if (const QJsonValue pageIdToken = token["pageIdToken"]; pageIdToken.isObject())
                return pageIdToken["pageId"].toString();
            else if (const QJsonValue keyToken = token["offlineCacheKeyToken"]; keyToken.isObject())
                return "UC" + keyToken["clientCacheKey"].toString();
        }

        return {};
    }
}