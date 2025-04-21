#include "performcommentaction.h"

namespace InnertubeEndpoints
{
    PerformCommentAction::PerformCommentAction(const QJsonValue& data)
    {
        response.actionResults = data["actionResults"].toArray();
        response.actions = data["actions"].toArray();
    }

    QJsonObject PerformCommentAction::createBody(const InnertubeContext* context, const QStringList& actions)
    {
        return {
            { "actions", QJsonArray::fromStringList(actions) },
            { "context", context->toJson() }
        };
    }

    QJsonObject PerformCommentAction::createBody(const InnertubeContext* context, const QString& action)
    {
        return createBody(context, QStringList(action));
    }
}
