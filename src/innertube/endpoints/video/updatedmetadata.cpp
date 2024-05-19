#include "updatedmetadata.h"
#include "innertube/innertubeexception.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    UpdatedMetadata::UpdatedMetadata(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& videoId)
    {
        const QJsonValue data = get(context, authStore, QJsonObject {
            EndpointMethods::contextPair(context),
            { "videoId", videoId }
        });

        const QJsonArray actions = data["actions"].toArray();
        if (actions.isEmpty())
            throw InnertubeException("[UpdatedMetadata] Actions not found or is empty");

        const QJsonValue likeCountEntity = data["frameworkUpdates"]["entityBatchUpdate"]["mutations"]
                                               [0]["payload"]["likeCountEntity"];
        if (!likeCountEntity.isObject())
            throw InnertubeException("[UpdatedMetadata] likeCountEntity not found");

        const QJsonValue updateDateTextAction = findAction(actions, "updateDateTextAction");
        const QJsonValue updateDescriptionAction = findAction(actions, "updateDescriptionAction");
        const QJsonValue updateTitleAction = findAction(actions, "updateTitleAction");
        const QJsonValue updateViewershipAction = findAction(actions, "updateViewershipAction");

        response.dateText = updateDateTextAction["dateText"]["simpleText"].toString();
        response.description = InnertubeObjects::InnertubeString(updateDescriptionAction["description"]);
        response.likeCountEntity = InnertubeObjects::LikeCountEntity(likeCountEntity);
        response.title = InnertubeObjects::InnertubeString(updateTitleAction["title"]);
        response.videoId = videoId;
        response.viewCount = InnertubeObjects::ViewCount(updateViewershipAction["viewCount"]["videoViewCountRenderer"]);
    }

    QJsonValue UpdatedMetadata::findAction(const QJsonArray& actions, const QString& name) const
    {
        auto actionIt = std::ranges::find_if(actions, [name](const QJsonValue& v) { return v[name].isObject(); });
        if (actionIt == actions.end())
            throw InnertubeException(QStringLiteral("[UpdatedMetadata] %1 not found").arg(name));
        return (*actionIt)[name];
    }
}
