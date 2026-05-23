#pragma once
#include "avatarstackviewmodel.h"
#include "buttonviewmodel.h"
#include "contentmetadataviewmodel.h"
#include "decoratedavatarviewmodel.h"

namespace InnertubeObjects
{
    struct LockupMetadataViewModel
    {
        std::variant<std::monostate, AvatarStackViewModel, DecoratedAvatarViewModel> image;
        ContentMetadataViewModel metadata;
        ButtonViewModel menuButton;
        QString title;

        LockupMetadataViewModel() = default;
        explicit LockupMetadataViewModel(const QJsonValue& lockupMetadataViewModel);
    };
}
