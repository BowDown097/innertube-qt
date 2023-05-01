#ifndef INVALIDATION_H
#define INVALIDATION_H
#include <QJsonValue>

namespace InnertubeObjects
{
    class Invalidation
    {
    public:
        QString objectId;
        int objectSource;
        QString protoCreationTimestampMs;
        bool subscribeToGcmTopics;
        QString topic;

        explicit Invalidation(const QJsonValue& invalidationId)
            : objectId(invalidationId["objectId"].toString()),
              objectSource(invalidationId["objectSource"].toInt()),
              protoCreationTimestampMs(invalidationId["protoCreationTimestampMs"].toString()),
              subscribeToGcmTopics(invalidationId["subscribeToGcmTopics"].toBool()),
              topic(invalidationId["topic"].toString()) {}
    };
}

#endif // INVALIDATION_H
