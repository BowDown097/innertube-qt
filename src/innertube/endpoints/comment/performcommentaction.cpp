#include "performcommentaction.h"

namespace InnertubeEndpoints
{
    PerformCommentAction::PerformCommentAction(const InnertubeContext* context, const InnertubeAuthStore* authStore,
                                               const QStringList& actions)
        : PerformCommentAction(get(context, authStore, createBody(context, actions))) {}

    PerformCommentAction::PerformCommentAction(const QJsonValue& data)
    {
        response.actionResults = data["actionResults"].toArray();
        response.actions = data["actions"].toArray();
    }

    QJsonObject PerformCommentAction::createBody(const InnertubeContext* context, const QStringList& actions)
    {
        return {
            { "actions", QJsonArray::fromStringList(actions) },
            EndpointMethods::contextPair(context)
        };
    }
}
