#include "updatedmetadata.h"
#include "innertube/innertubeexception.h"
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    UpdatedMetadata::UpdatedMetadata(const QString& videoId, InnertubeContext* context, InnertubeAuthStore* authStore)
    {
        const QJsonObject body {
            { "context", context->toJson() },
            { "videoId", videoId }
        };

        QByteArray data = get("updated_metadata", context, authStore, body);
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
        response.isLive = updateViewershipAction["viewCount"]["videoViewCountRenderer"]["isLive"].toBool();
        response.likeDefaultText = updateToggleButtonTextAction["defaultText"]["simpleText"].toString();
        response.likeToggledText = updateToggleButtonTextAction["toggledText"]["simpleText"].toString();
        response.title = InnertubeObjects::InnertubeString(updateTitleAction["title"]);
        response.videoId = videoId;
        response.viewCount = updateViewershipAction["viewCount"]["videoViewCountRenderer"]["viewCount"]["simpleText"].toString();
    }

    QJsonValue UpdatedMetadata::findAction(const QJsonArray& actions, const QString& name)
    {
        QJsonArray::const_iterator actionIt = std::ranges::find_if(actions, [name](const QJsonValue& v) { return v[name].isObject(); });

        if (actionIt == actions.cend())
        {
            throw InnertubeException(QStringLiteral("[UpdatedMetadata] %1 not found").arg(name));
            return QJsonValue();
        }

        return (*actionIt)[name];
    }
}
