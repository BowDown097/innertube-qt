#pragma once
#include "lockupmetadataviewmodel.h"
#include "thumbnailviewmodel.h"

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
    };
}
