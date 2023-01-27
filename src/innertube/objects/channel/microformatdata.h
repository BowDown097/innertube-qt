#ifndef MICROFORMATDATA_H
#define MICROFORMATDATA_H
#include "innertube/objects/genericthumbnail.h"

namespace InnertubeObjects
{
    class MicroformatData
    {
    public:
        QString androidPackage;
        QString appName;
        QList<QString> availableCountries;
        QString description;
        bool familySafe;
        QString iosAppArguments;
        QString iosAppStoreId;
        QList<QString> linkAlternates;
        bool noIndex;
        QString ogType;
        QString schemaDotOrgType;
        QString siteName;
        QList<QString> tags;
        QList<GenericThumbnail> thumbnails;
        QString title;
        QString twitterCardType;
        QString twitterSiteHandle;
        bool unlisted;
        QString urlAppLinksAndroid;
        QString urlAppLinksIos;
        QString urlAppLinksWeb;
        QString urlCanonical;
        QString urlTwitterAndroid;
        QString urlTwitterIos;

        MicroformatData() {}
        explicit MicroformatData(const QJsonValue& microformatDataRenderer);
    };
}
#endif // MICROFORMATDATA_H
