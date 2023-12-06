#ifndef CHANNELMETADATA_H
#define CHANNELMETADATA_H
#include "innertube/objects/responsiveimage.h"

namespace InnertubeObjects
{
    struct ChannelMetadata
    {
        QString androidAppIndexingLink;
        QString androidDeepLink;
        QStringList availableCountryCodes;
        ResponsiveImage avatar;
        QString channelConversionUrl;
        QString channelUrl;
        QString description;
        QString doubleClickTrackingUsername;
        QString externalId;
        QString facebookProfileId;
        QString iosAppIndexingLink;
        bool isFamilySafe;
        QString keywords;
        QStringList ownerUrls;
        QString rssUrl;
        QString title;
        QString vanityChannelUrl;

        ChannelMetadata() = default;
        explicit ChannelMetadata(const QJsonValue& channelMetadataRenderer);
    };
}

#endif // CHANNELMETADATA_H
