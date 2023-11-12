#include "updatedmetadata.h"
#include "innertube/innertubeexception.h"
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    UpdatedMetadata::UpdatedMetadata(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& videoId)
    {
        const QJsonObject body {
            { "context", context->toJson() },
            { "videoId", videoId }
        };

        QByteArray data = get(context, authStore, body);
        QJsonValue dataObj = QJsonDocument::fromJson(data).object();

        QJsonArray actions = dataObj["actions"].toArray();
        if (actions.isEmpty())
            throw InnertubeException("[UpdatedMetadata] Actions not found or is empty");

        QJsonValue updateDateTextAction = findAction(actions, "updateDateTextAction");
        QJsonValue updateDescriptionAction = findAction(actions, "updateDescriptionAction");
        QJsonValue updateTitleAction = findAction(actions, "updateTitleAction");
        QJsonValue updateToggleButtonTextAction = findAction(actions, "updateToggleButtonTextAction");
        QJsonValue updateViewershipAction = findAction(actions, "updateViewershipAction");

        response.dateText = updateDateTextAction["dateText"]["simpleText"].toString();
        response.description = InnertubeObjects::InnertubeString(updateDescriptionAction["description"]);
        response.likeDefaultText = updateToggleButtonTextAction["defaultText"]["simpleText"].toString();
        response.likeNumericalValue = updateToggleButtonTextAction["defaultNumericalValue"].toString();
        response.likeToggledText = updateToggleButtonTextAction["toggledText"]["simpleText"].toString();
        response.title = InnertubeObjects::InnertubeString(updateTitleAction["title"]);
        response.videoId = videoId;
        response.viewCount = InnertubeObjects::ViewCount(updateViewershipAction["viewCount"]["videoViewCountRenderer"]);
    }

    QJsonValue UpdatedMetadata::findAction(const QJsonArray& actions, const QString& name)
    {
        auto actionIt = std::ranges::find_if(actions, [name](const QJsonValue& v) { return v[name].isObject(); });
        if (actionIt == actions.end())
            throw InnertubeException(QStringLiteral("[UpdatedMetadata] %1 not found").arg(name));
        return (*actionIt)[name];
    }
}
