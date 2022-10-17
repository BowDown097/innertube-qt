#ifndef VIDEOPRIMARYINFO_H
#define VIDEOPRIMARYINFO_H
#include "../innertubestring.h"
#include <QJsonObject>
#include <QRegularExpression>

namespace InnertubeObjects
{
    class VideoPrimaryInfo
    {
    public:
        InnertubeString dateText;
        int likeCount;
        InnertubeString relativeDateText;
        InnertubeString shortViewCount;
        InnertubeString title;
        InnertubeString viewCount;

        VideoPrimaryInfo() {}
        explicit VideoPrimaryInfo(const QJsonValue& primaryInfoRenderer);
    private:
        static inline const QRegularExpression numberRegex = QRegularExpression("\\d");
        QJsonValue primaryInfoRenderer;
        QJsonValue retrieveTopLevelButton(const QString& targetId);
    };
}

#endif // VIDEOPRIMARYINFO_H
