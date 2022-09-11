#ifndef CAPTIONTRACK_H
#define CAPTIONTRACK_H
#include "../innertubestring.h"

namespace InnertubeObjects
{
    class CaptionTrack
    {
    public:
        QString baseUrl;
        bool isTranslatable;
        QString kind;
        QString languageCode;
        InnertubeString name;
        QString vssId;

        CaptionTrack(const QJsonObject& captionTrack)
        {
            baseUrl = captionTrack["baseUrl"].toString();
            isTranslatable = captionTrack["isTranslatable"].toBool();
            kind = captionTrack["kind"].toString();
            languageCode = captionTrack["languageCode"].toString();
            name = InnertubeString(captionTrack["name"]);
            vssId = captionTrack["vssId"].toString();
        }
    };
}

#endif // CAPTIONTRACK_H
