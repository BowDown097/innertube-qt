#pragma once
#include "innertube/objects/video/videoowner.h"
#include "lockupmetadataviewmodel.h"
#include "thumbnailviewmodel.h"
#include <optional>

namespace InnertubeObjects
{
    struct LockupViewModel
    {
        QString contentId;
        ThumbnailViewModel contentImage;
        QString contentType;
        QJsonValue itemPlayback;
        LockupMetadataViewModel metadata;
        QJsonValue rendererContext;

        LockupViewModel() = default;
        explicit LockupViewModel(const QJsonValue& lockupViewModel)
            : contentId(lockupViewModel["contentId"].toString()),
              contentImage(lockupViewModel["contentImage"]["thumbnailViewModel"]),
              contentType(lockupViewModel["contentType"].toString()),
              itemPlayback(lockupViewModel["itemPlayback"]),
              rendererContext(lockupViewModel["rendererContext"]) {}

        bool isLive() const;
        QTime length() const;
        QString lengthText() const;
        std::optional<VideoOwner> owner() const;
    };
}
