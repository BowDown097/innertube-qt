#ifndef ACTIVEACCOUNTHEADER_H
#define ACTIVEACCOUNTHEADER_H
#include "innertube/objects/responsiveimage.h"

namespace InnertubeObjects
{
    struct ActiveAccountHeader
    {
        QString accountName;
        ResponsiveImage accountPhoto;
        QString channelHandle;
        QJsonValue manageAccountEndpoint;
        QJsonValue settingsEndpoint;

        ActiveAccountHeader() = default;
        explicit ActiveAccountHeader(const QJsonValue& activeAccountHeaderRenderer)
            : accountName(activeAccountHeaderRenderer["accountName"]["simpleText"].toString()),
              accountPhoto(activeAccountHeaderRenderer["accountPhoto"]["thumbnails"]),
              channelHandle(activeAccountHeaderRenderer["channelHandle"]["simpleText"].toString()),
              manageAccountEndpoint(activeAccountHeaderRenderer["manageAccountTitle"]["runs"][0]["navigationEndpoint"]),
              settingsEndpoint(activeAccountHeaderRenderer["settingsEndpoint"]) {}
    };
}

#endif // ACTIVEACCOUNTHEADER_H
