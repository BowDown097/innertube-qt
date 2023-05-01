#ifndef INVALIDATIONCONTINUATION_H
#define INVALIDATIONCONTINUATION_H
#include "invalidation.h"

namespace InnertubeObjects
{
    class InvalidationContinuation
    {
    public:
        QString continuation;
        Invalidation invalidationId;
        int timeoutMs;

        explicit InvalidationContinuation(const QJsonValue& invalidationContinuationData)
            : continuation(invalidationContinuationData["continuation"].toString()),
              invalidationId(invalidationContinuationData["invalidationId"]),
              timeoutMs(invalidationContinuationData["timeoutMs"].toInt()) {}
    };
}

#endif // INVALIDATIONCONTINUATION_H
