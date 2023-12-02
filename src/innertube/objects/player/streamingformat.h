#ifndef STREAMINGFORMAT_H
#define STREAMINGFORMAT_H
#include <QJsonValue>

namespace InnertubeObjects
{
    struct StreamingFormat
    {
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

        explicit StreamingFormat(const QJsonValue& format)
            : approxDurationMs(format["approxDurationMs"].toString()),
              averageBitrate(format["averageBitrate"].toVariant().toLongLong()),
              bitrate(format["bitrate"].toVariant().toLongLong()),
              contentLength(format["contentLength"].toString()),
              fps(format["fps"].toInt()),
              height(format["height"].toInt()),
              indexRangeStart(format["indexRange"]["start"].toString()),
              indexRangeEnd(format["indexRange"]["end"].toString()),
              initRangeStart(format["initRange"]["start"].toString()),
              initRangeEnd(format["initRange"]["end"].toString()),
              itag(format["itag"].toInt()),
              lastModified(format["lastModified"].toString()),
              mimeType(format["mimeType"].toString()),
              projectionType(format["projectionType"].toString()),
              quality(format["quality"].toString()),
              qualityLabel(format["qualityLabel"].toString()),
              url(format["url"].toString()),
              width(format["width"].toInt()) {}
    };
}

#endif // STREAMINGFORMAT_H
