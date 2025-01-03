#include "basevideo.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    BaseVideo::BaseVideo(const QJsonValue& renderer)
        : lengthText(renderer["lengthText"]),
          longBylineText(renderer["longBylineText"]),
          menu(renderer["menu"]["menuRenderer"]),
          navigationEndpoint(renderer["navigationEndpoint"]),
          shortBylineText(renderer["shortBylineText"]),
          thumbnail(renderer["thumbnail"]),
          title(renderer["title"]),
          videoId(renderer["videoId"].toString())
    {
        const QJsonArray thumbnailOverlaysJson = renderer["thumbnailOverlays"].toArray();
        for (const QJsonValue& overlay : thumbnailOverlaysJson)
        {
            if (const QJsonValue endorsement = overlay["thumbnailOverlayEndorsementRenderer"]; endorsement.isObject())
                thumbnailOverlays.append(ThumbnailOverlayEndorsement(endorsement));
            else if (const QJsonValue inlineUnplayable = overlay["thumbnailOverlayInlineUnplayableRenderer"]; inlineUnplayable.isObject())
                thumbnailOverlays.append(ThumbnailOverlayInlineUnplayable(inlineUnplayable));
            else if (const QJsonValue loadingPreview = overlay["thumbnailOverlayLoadingPreviewRenderer"]; loadingPreview.isObject())
                thumbnailOverlays.append(ThumbnailOverlayLoadingPreview(loadingPreview));
            else if (const QJsonValue nowPlaying = overlay["thumbnailOverlayNowPlayingRenderer"]; nowPlaying.isObject())
                thumbnailOverlays.append(ThumbnailOverlayNowPlaying(nowPlaying));
            else if (const QJsonValue resumePlayback = overlay["thumbnailOverlayResumePlaybackRenderer"]; resumePlayback.isObject())
                thumbnailOverlays.append(ThumbnailOverlayResumePlayback(resumePlayback));
            else if (const QJsonValue timeStatus = overlay["thumbnailOverlayTimeStatusRenderer"]; timeStatus.isObject())
                thumbnailOverlays.append(ThumbnailOverlayTimeStatus(timeStatus));
            else if (const QJsonValue toggleButton = overlay["thumbnailOverlayToggleButtonRenderer"]; toggleButton.isObject())
                thumbnailOverlays.append(ThumbnailOverlayToggleButton(toggleButton));
        }
    }

    QTime BaseVideo::length() const
    {
        const InnertubeString& lengthDisplayText = lengthDisplay();

        QTime out = QTime::fromString(lengthDisplayText.text, "h:mm:ss");
        if (!out.isValid())
            out = QTime::fromString(lengthDisplayText.text, "m:ss");

        return out;
    }

    const InnertubeString& BaseVideo::lengthDisplay() const
    {
        for (const ThumbnailOverlay& overlay : thumbnailOverlays)
            if (const ThumbnailOverlayTimeStatus* timeStatus = std::get_if<ThumbnailOverlayTimeStatus>(&overlay))
                return timeStatus->text;

        return lengthText;
    }
}
