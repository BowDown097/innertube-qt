#pragma once
#include <QJsonValue>

namespace InnertubeObjects
{
    struct EntityMutation
    {
        QString entityKey;
        QJsonValue payload;
        QString type;

        EntityMutation() = default;
        explicit EntityMutation(const QJsonValue& mutation)
            : entityKey(mutation["entityKey"].toString()),
              payload(mutation["payload"]),
              type(mutation["type"].toString()) {}
    };
}
