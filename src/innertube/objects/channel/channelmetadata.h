#ifndef CHANNELMETADATA_H
#define CHANNELMETADATA_H
#include "innertube/objects/genericthumbnail.h"

namespace InnertubeObjects
{
    class ChannelMetadata
    {
    public:
        QString androidAppIndexingLink;
        QString androidDeepLink;
        QList<QString> availableCountryCodes;
        QList<GenericThumbnail> avatar;
        QString channelConversionUrl;
        QString channelUrl;
        QString description;
        QString doubleClickTrackingUsername;
        QString externalId;
        QString facebookProfileId;
        QString iosAppIndexingLink;
        bool isFamilySafe = false;
        QString keywords;
        QList<QString> ownerUrls;
        QString rssUrl;
        QString title;
        QString vanityChannelUrl;

        ChannelMetadata() = default;
        explicit ChannelMetadata(const QJsonValue& channelMetadataRenderer);
    };
}

#endif // CHANNELMETADATA_H
