#include "activeaccountheader.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    ActiveAccountHeader::ActiveAccountHeader(const QJsonValue& activeAccountHeaderRenderer)
        : accountName(activeAccountHeaderRenderer["accountName"]["simpleText"].toString()),
          channelHandle(activeAccountHeaderRenderer["channelHandle"]["simpleText"].toString())
    {
        const QJsonArray accountPhotoJson = activeAccountHeaderRenderer["accountPhoto"]["thumbnails"].toArray();
        for (const QJsonValue& v : accountPhotoJson)
            accountPhoto.append(GenericThumbnail(v));
    }
}
