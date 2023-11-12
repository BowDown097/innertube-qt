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
        QStringList availableCountries;
        QString description;
        bool familySafe = false;
        QString iosAppArguments;
        QString iosAppStoreId;
        QStringList linkAlternates;
        bool noIndex = false;
        QString ogType;
        QString schemaDotOrgType;
        QString siteName;
        QStringList tags;
        QList<GenericThumbnail> thumbnails;
        QString title;
        QString twitterCardType;
        QString twitterSiteHandle;
        bool unlisted = false;
        QString urlAppLinksAndroid;
        QString urlAppLinksIos;
        QString urlAppLinksWeb;
        QString urlCanonical;
        QString urlTwitterAndroid;
        QString urlTwitterIos;

        MicroformatData() = default;
        explicit MicroformatData(const QJsonValue& microformatDataRenderer);
    };
}
#endif // MICROFORMATDATA_H
