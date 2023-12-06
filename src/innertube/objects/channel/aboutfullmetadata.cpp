#include "aboutfullmetadata.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    AboutFullMetadata::AboutFullMetadata(const QJsonValue& renderer)
        : avatar(renderer["avatar"]["thumbnails"]),
          bypassBusinessEmailCaptcha(renderer["bypassBusinessEmailCaptcha"].toBool()),
          canonicalChannelUrl(renderer["canonicalChannelUrl"].toString()),
          channelId(renderer["channelId"].toString()),
          country(renderer["country"]["simpleText"].toString()),
          countryLabel(renderer["countryLabel"]),
          description(renderer["description"]["simpleText"].toString()),
          descriptionLabel(renderer["descriptionLabel"]),
          detailsLabel(renderer["detailsLabel"]),
          joinedDateText(renderer["joinedDateText"]),
          primaryLinksLabel(renderer["primaryLinksLabel"]),
          showDescription(renderer["showDescription"].toBool()),
          statsLabel(renderer["statsLabel"]),
          title(renderer["title"]["simpleText"].toString()),
          viewCountText(renderer["viewCountText"]["simpleText"].toString())
    {
        const QJsonArray actionButtonsJson = renderer["actionButtons"].toArray();
        for (const QJsonValue& v : actionButtonsJson)
            actionButtons.append(Button(v["buttonRenderer"]));

        const QJsonArray primaryLinksJson = renderer["primaryLinks"].toArray();
        for (const QJsonValue& v : primaryLinksJson)
            primaryLinks.append(ChannelHeaderLink(v));
    }
}
