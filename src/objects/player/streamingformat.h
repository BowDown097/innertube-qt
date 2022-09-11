#ifndef STREAMINGFORMAT_H
#define STREAMINGFORMAT_H
#include <QJsonObject>
#include <QString>

namespace InnertubeObjects
{
    class StreamingFormat
    {
    public:
        QString approxDurationMs;
        long averageBitrate;
        long bitrate;
        QString contentLength;
        int fps;
        int height;
        QString indexRangeStart;
        QString indexRangeEnd;
        QString initRangeStart;
        QString initRangeEnd;
        int itag;
        QString lastModified;
        QString mimeType;
        QString projectionType;
        QString quality;
        QString qualityLabel;
        QString url;
        int width;

        StreamingFormat(const QJsonObject& format)
        {
            approxDurationMs = format["approxDurationMs"].toString();
            averageBitrate = format["averageBitrate"].toInteger();
            bitrate = format["bitrate"].toInteger();
            contentLength = format["contentLength"].toString();
            fps = format["fps"].toInt();
            height = format["height"].toInt();
            itag = format["itag"].toInt();
            lastModified = format["lastModified"].toString();
            mimeType = format["mimeType"].toString();
            projectionType = format["projectionType"].toString();
            quality = format["quality"].toString();
            qualityLabel = format["qualityLabel"].toString();
            url = format["url"].toString();
            width = format["width"].toInt();

            QJsonObject indexRange = format["indexRange"].toObject();
            QJsonObject initRange = format["initRange"].toObject();

            indexRangeStart = indexRange["start"].toString();
            indexRangeEnd = indexRange["end"].toString();
            initRangeStart = initRange["start"].toString();
            initRangeEnd = initRange["end"].toString();
        }
    };
}

#endif // STREAMINGFORMAT_H
