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
        explicit StreamingFormat(const QJsonObject& format);
    };
}

#endif // STREAMINGFORMAT_H
