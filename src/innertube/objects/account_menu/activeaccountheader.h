#pragma once
#include "innertube/objects/images/responsiveimage.h"
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    struct ActiveAccountHeader
    {
        QString accountName;
        ResponsiveImage accountPhoto;
        QString channelHandle;
        InnertubeString manageAccountTitle;
        QJsonValue settingsEndpoint;

        ActiveAccountHeader() = default;
        explicit ActiveAccountHeader(const QJsonValue& activeAccountHeaderRenderer)
            : accountName(activeAccountHeaderRenderer["accountName"]["simpleText"].toString()),
              accountPhoto(activeAccountHeaderRenderer["accountPhoto"]["thumbnails"]),
              channelHandle(activeAccountHeaderRenderer["channelHandle"]["simpleText"].toString()),
              manageAccountTitle(activeAccountHeaderRenderer["manageAccountTitle"]),
              settingsEndpoint(activeAccountHeaderRenderer["settingsEndpoint"]) {}
    };
}
