#include "microformatdata.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    MicroformatData::MicroformatData(const QJsonValue& microformatDataRenderer)
        : androidPackage(microformatDataRenderer["androidPackage"].toString()),
          appName(microformatDataRenderer["appName"].toString()),
          description(microformatDataRenderer["description"].toString()),
          familySafe(microformatDataRenderer["familySafe"].toBool()),
          iosAppArguments(microformatDataRenderer["iosAppArguments"].toString()),
          iosAppStoreId(microformatDataRenderer["iosAppStoreId"].toString()),
          noIndex(microformatDataRenderer["noindex"].toBool()),
          ogType(microformatDataRenderer["ogType"].toString()),
          schemaDotOrgType(microformatDataRenderer["schemaDotOrgType"].toString()),
          siteName(microformatDataRenderer["siteName"].toString()),
          thumbnail(microformatDataRenderer["thumbnails"]),
          title(microformatDataRenderer["title"].toString()),
          twitterCardType(microformatDataRenderer["twitterCardType"].toString()),
          twitterSiteHandle(microformatDataRenderer["twitterSiteHandle"].toString()),
          unlisted(microformatDataRenderer["unlisted"].toBool()),
          urlAppLinksAndroid(microformatDataRenderer["urlApplinksAndroid"].toString()),
          urlAppLinksIos(microformatDataRenderer["urlApplinksIos"].toString()),
          urlAppLinksWeb(microformatDataRenderer["urlApplinksWeb"].toString()),
          urlCanonical(microformatDataRenderer["urlCanonical"].toString()),
          urlTwitterAndroid(microformatDataRenderer["urlTwitterAndroid"].toString()),
          urlTwitterIos(microformatDataRenderer["urlTwitterIos"].toString())
    {
        const QJsonArray availableCountriesJson = microformatDataRenderer["availableCountries"].toArray();
        for (const QJsonValue& v : availableCountriesJson)
            availableCountries.append(v.toString());

        const QJsonArray linkAlternatesJson = microformatDataRenderer["linkAlternates"].toArray();
        for (const QJsonValue& v : linkAlternatesJson)
            linkAlternates.append(v["hrefUrl"].toString());

        const QJsonArray tagsJson = microformatDataRenderer["tags"].toArray();
        for (const QJsonValue& v : tagsJson)
            tags.append(v.toString());
    }
}
