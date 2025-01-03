#include "lockupviewmodel.h"

namespace InnertubeObjects
{
    bool LockupViewModel::isLive() const
    {
        return std::ranges::any_of(contentImage.overlays, [](const auto& overlay) {
            if (const ThumbnailOverlayBadgeViewModel* badgeOverlay = std::get_if<ThumbnailOverlayBadgeViewModel>(&overlay))
            {
                return std::ranges::any_of(badgeOverlay->thumbnailBadges, [](const ThumbnailBadgeViewModel& badge) {
                    return badge.badgeStyle == "THUMBNAIL_OVERLAY_BADGE_STYLE_LIVE";
                });
            }

            return false;
        });
    }

    QTime LockupViewModel::length() const
    {
        if (QString text = lengthText(); !text.isEmpty())
        {
            QTime out = QTime::fromString(text, "h:mm:ss");
            if (!out.isValid())
                out = QTime::fromString(text, "m:ss");
            return out;
        }

        return QTime();
    }

    QString LockupViewModel::lengthText() const
    {
        for (const auto& overlay : contentImage.overlays)
        {
            const ThumbnailOverlayBadgeViewModel* badgeOverlay = std::get_if<ThumbnailOverlayBadgeViewModel>(&overlay);
            if (badgeOverlay && !badgeOverlay->thumbnailBadges.empty())
                return badgeOverlay->thumbnailBadges.constFirst().text;
        }

        return QString();
    }

    std::optional<VideoOwner> LockupViewModel::owner() const
    {
        const QList<QList<DynamicText>>& metadataRows = metadata.metadata.metadataRows;
        if (metadataRows.empty() || metadataRows[0].empty())
            return std::nullopt;

        return VideoOwner {
            .icon = metadata.image.avatar.image,
            .id = metadataRows[0][0].commandRuns[0]["onTap"]["innertubeCommand"]["browseEndpoint"]["browseId"].toString(),
            .name = metadataRows[0][0].content
        };
    }
}
