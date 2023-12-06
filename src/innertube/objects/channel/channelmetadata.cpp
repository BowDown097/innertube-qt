#include "channelmetadata.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    ChannelMetadata::ChannelMetadata(const QJsonValue& channelMetadataRenderer)
        : androidAppIndexingLink(channelMetadataRenderer["androidAppindexingLink"].toString()),
          androidDeepLink(channelMetadataRenderer["androidDeepLink"].toString()),
          avatar(channelMetadataRenderer["avatar"]),
          channelConversionUrl(channelMetadataRenderer["channelConversionUrl"].toString()),
          channelUrl(channelMetadataRenderer["channelUrl"].toString()),
          description(channelMetadataRenderer["description"].toString()),
          doubleClickTrackingUsername(channelMetadataRenderer["doubleclickTrackingUsername"].toString()),
          externalId(channelMetadataRenderer["externalId"].toString()),
          facebookProfileId(channelMetadataRenderer["facebookProfileId"].toString()),
          iosAppIndexingLink(channelMetadataRenderer["iosAppindexingLink"].toString()),
          isFamilySafe(channelMetadataRenderer["isFamilySafe"].toBool()),
          keywords(channelMetadataRenderer["keywords"].toString()),
          rssUrl(channelMetadataRenderer["rssUrl"].toString()),
          title(channelMetadataRenderer["title"].toString()),
          vanityChannelUrl(channelMetadataRenderer["vanityChannelUrl"].toString())
    {
        const QJsonArray availableCountriesJson = channelMetadataRenderer["availableCountryCodes"].toArray();
        for (const QJsonValue& v : availableCountriesJson)
            availableCountryCodes.append(v.toString());

        const QJsonArray ownerUrlsJson = channelMetadataRenderer["ownerUrls"].toArray();
        for (const QJsonValue& v : ownerUrlsJson)
            ownerUrls.append(v.toString());
    }
}
