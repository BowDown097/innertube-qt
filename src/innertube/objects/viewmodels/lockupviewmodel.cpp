#include "lockupviewmodel.h"

namespace InnertubeObjects
{
    bool LockupViewModel::isLive() const
    {
        return std::ranges::any_of(contentImage.overlays, [](const ThumbnailViewModelOverlay& overlay) {
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
        for (const ThumbnailViewModelOverlay& overlay : contentImage.overlays)
        {
            if (const auto* badge = std::get_if<ThumbnailOverlayBadgeViewModel>(&overlay);
                badge && !badge->thumbnailBadges.empty())
            {
                return badge->thumbnailBadges.constFirst().text;
            }
            else if (const auto* bottom = std::get_if<ThumbnailBottomOverlayViewModel>(&overlay);
                     bottom && !bottom->badges.empty())
            {
                auto it = std::ranges::find_if_not(bottom->badges, &QString::isEmpty, &ThumbnailBadgeViewModel::text);
                if (it != bottom->badges.end())
                    return it->text;
            }
        }

        return QString();
    }

    std::optional<BasicChannel> LockupViewModel::owner() const
    {
        if (const QList<ContentMetadataRow>& metadataRows = metadata.metadata.metadataRows; !metadataRows.empty())
        {
            if (const auto* dynamicText = std::get_if<QList<DynamicText>>(&metadataRows[0].content))
            {
                if (const auto* avatar = std::get_if<DecoratedAvatarViewModel>(&metadata.image))
                {
                    QString channelId = dynamicText->at(0).commandRuns[0]["onTap"]["innertubeCommand"]["browseEndpoint"]["browseId"].toString();
                    if (channelId.isEmpty())
                        channelId = avatar->rendererContext["commandContext"]["onTap"]["innertubeCommand"]["browseEndpoint"]["browseId"].toString();

                    return BasicChannel {
                        .icon = avatar->avatar.image,
                        .id = channelId,
                        .name = dynamicText->at(0).content
                    };
                }
                else if (const auto* stack = std::get_if<AvatarStackViewModel>(&metadata.image))
                {
                    return BasicChannel {
                        .icon = stack->avatars[0].image,
                        .id = stack->rendererContext["commandContext"]["onTap"]["innertubeCommand"]
                            ["showDialogCommand"]["panelLoadingStrategy"]["inlineContent"]
                            ["dialogViewModel"]["customContent"]["listViewModel"]["listItems"]
                            [0]["listItemViewModel"]["rendererContext"]["commandContext"]
                            ["onTap"]["innertubeCommand"]["browseEndpoint"]["browseId"].toString(),
                        .name = dynamicText->at(0).content
                    };
                }
                else if (dynamicText->at(0).commandRuns.isArray())
                {
                    return BasicChannel {
                        .id = dynamicText->at(0).commandRuns[0]["onTap"]["innertubeCommand"]["browseEndpoint"]["browseId"].toString(),
                        .name = dynamicText->at(0).content
                    };
                }
            }
        }

        return std::nullopt;
    }
}
