#ifndef CAPTIONTRACK_H
#define CAPTIONTRACK_H
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    struct CaptionTrack
    {
        QString baseUrl;
        bool isTranslatable;
        QString kind;
        QString languageCode;
        InnertubeString name;
        QString vssId;

        explicit CaptionTrack(const QJsonValue& captionTrack)
            : baseUrl(captionTrack["baseUrl"].toString()),
              isTranslatable(captionTrack["isTranslatable"].toBool()),
              kind(captionTrack["kind"].toString()),
              languageCode(captionTrack["languageCode"].toString()),
              name(InnertubeString(captionTrack["name"])),
              vssId(captionTrack["vssId"].toString()) {}
    };
}

#endif // CAPTIONTRACK_H
