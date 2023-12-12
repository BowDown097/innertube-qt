#include "performcommentaction.h"
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    PerformCommentAction::PerformCommentAction(InnertubeContext* context, InnertubeAuthStore* authStore,
                                               const QStringList& actions)
    {
        const QJsonObject body {
            { "actions", QJsonArray::fromStringList(actions) },
            { "context", context->toJson() }
        };

        QByteArray data = get(context, authStore, body);
        QJsonValue dataObj = QJsonDocument::fromJson(data).object();

        response.actionResults = dataObj["actionResults"].toArray();
        response.actions = dataObj["actions"].toArray();
    }
}
