#pragma once
#include "innertube/objects/responsiveimage.h"

namespace InnertubeObjects
{
    struct MicroformatData
    {
        QString androidPackage;
        QString appName;
        QStringList availableCountries;
        QString description;
        bool familySafe{};
        QString iosAppArguments;
        QString iosAppStoreId;
        QStringList linkAlternates;
        bool noIndex{};
        QString ogType;
        QString schemaDotOrgType;
        QString siteName;
        QStringList tags;
        ResponsiveImage thumbnail;
        QString title;
        QString twitterCardType;
        QString twitterSiteHandle;
        bool unlisted{};
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
