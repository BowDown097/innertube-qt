#pragma once
#include "buttonviewmodel.h"
#include "contentmetadataviewmodel.h"
#include "decoratedavatarviewmodel.h"

namespace InnertubeObjects
{
    struct LockupMetadataViewModel
    {
        DecoratedAvatarViewModel image;
        ContentMetadataViewModel metadata;
        ButtonViewModel menuButton;
        QString title;

        LockupMetadataViewModel() = default;
        explicit LockupMetadataViewModel(const QJsonValue& lockupMetadataViewModel)
            : image(lockupMetadataViewModel["image"]["decoratedAvatarViewModel"]),
              metadata(lockupMetadataViewModel["metadata"]["contentMetadataViewModel"]),
              menuButton(lockupMetadataViewModel["menuButton"]["buttonViewModel"]),
              title(lockupMetadataViewModel["title"]["content"].toString()) {}
    };
}
