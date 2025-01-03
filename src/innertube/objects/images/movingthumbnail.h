#pragma once
#include "responsiveimage.h"

namespace InnertubeObjects
{
    struct MovingThumbnailDetails
    {
        bool logAsMovingThumbnail{};
        ResponsiveImage thumbnail;

        MovingThumbnailDetails() = default;
        explicit MovingThumbnailDetails(const QJsonValue& movingThumbnailDetails)
            : logAsMovingThumbnail(movingThumbnailDetails["logAsMovingThumbnail"].toBool()),
              thumbnail(movingThumbnailDetails["thumbnails"]) {}
    };

    struct MovingThumbnail
    {
        bool enableHoveredLogging{};
        bool enableOverlay{};
        MovingThumbnailDetails movingThumbnailDetails;

        MovingThumbnail() = default;
        explicit MovingThumbnail(const QJsonValue& movingThumbnailRenderer)
            : enableHoveredLogging(movingThumbnailRenderer["enableHoveredLogging"].toBool()),
              enableOverlay(movingThumbnailRenderer["enableOverlay"].toBool()),
              movingThumbnailDetails(movingThumbnailRenderer["movingThumbnailDetails"]) {}
    };
}
