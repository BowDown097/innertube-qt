#include "activeaccountheader.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    ActiveAccountHeader::ActiveAccountHeader(const QJsonValue& activeAccountHeaderRenderer)
        : accountName(activeAccountHeaderRenderer["accountName"]["simpleText"].toString()),
          channelHandle(activeAccountHeaderRenderer["channelHandle"]["simpleText"].toString()),
          manageAccountEndpoint(activeAccountHeaderRenderer["manageAccountTitle"]["runs"][0]["navigationEndpoint"]),
          settingsEndpoint(activeAccountHeaderRenderer["settingsEndpoint"])
    {
        const QJsonArray accountPhotosJson = activeAccountHeaderRenderer["accountPhoto"]["thumbnails"].toArray();
        for (const QJsonValue& v : accountPhotosJson)
            accountPhotos.append(GenericThumbnail(v));
    }
}
