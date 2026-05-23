#include "lockupmetadataviewmodel.h"

namespace InnertubeObjects
{
    LockupMetadataViewModel::LockupMetadataViewModel(const QJsonValue& lockupMetadataViewModel)
        : metadata(lockupMetadataViewModel["metadata"]["contentMetadataViewModel"]),
          menuButton(lockupMetadataViewModel["menuButton"]["buttonViewModel"]),
          title(lockupMetadataViewModel["title"]["content"].toString())
    {
        if (const QJsonValue avatar = lockupMetadataViewModel["image"]["decoratedAvatarViewModel"]; avatar.isObject())
            image = DecoratedAvatarViewModel(avatar);
        else if (const QJsonValue stack = lockupMetadataViewModel["image"]["avatarStackViewModel"]; stack.isObject())
            image = AvatarStackViewModel(stack);
    }
}