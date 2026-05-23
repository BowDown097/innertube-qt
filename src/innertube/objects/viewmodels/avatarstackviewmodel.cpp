#include "avatarstackviewmodel.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    AvatarStackViewModel::AvatarStackViewModel(const QJsonValue& avatarStackViewModel)
        : avatarClusterSize(avatarStackViewModel["avatarClusterSize"].toString()),
          layoutType(avatarStackViewModel["layoutType"].toString()),
          rendererContext(avatarStackViewModel["rendererContext"])
    {
        const QJsonArray avatarsJson = avatarStackViewModel["avatars"].toArray();
        for (const QJsonValue& avatar : avatarsJson)
            avatars.emplaceBack(avatar["avatarViewModel"]);
    }
}