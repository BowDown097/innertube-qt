#include "browsehome.h"
#include "innertube/innertubeexception.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    BrowseHome::BrowseHome(const InnertubeContext* context, const InnertubeAuthStore* authStore, const QString& tokenIn)
        : BrowseHome(fetch("FEwhat_to_watch", context, authStore, tokenIn)) {}

    BrowseHome::BrowseHome(const QJsonValue& data)
    {
        QJsonArray contents;
        if (const QJsonValue continuationContents = data["continuationContents"]; continuationContents.isObject())
        {
            const QJsonValue richGridContinuation = continuationContents["richGridContinuation"];
            if (!richGridContinuation.isObject())
                throw InnertubeException("[BrowseHome] richGridContinuation not found");

            contents = richGridContinuation["contents"].toArray();
        }
        else if (const QJsonValue baseContents = data["contents"]; baseContents.isObject())
        {
            const QLatin1String baseRenderer(!baseContents["twoColumnBrowseResultsRenderer"].isUndefined()
                                             ? "twoColumnBrowseResultsRenderer" : "singleColumnBrowseResultsRenderer");
            const QJsonValue resultsRenderer = baseContents[baseRenderer];
            if (!resultsRenderer.isObject())
                throw InnertubeException(QStringLiteral("[BrowseHome] %1 not found").arg(baseRenderer));

            const QJsonArray tabs = resultsRenderer["tabs"].toArray();
            if (tabs.isEmpty())
                throw InnertubeException("[BrowseHome] tabs not found or is empty");

            const QJsonValue tabRenderer = tabs[0]["tabRenderer"]["content"];
            if (!tabRenderer.isObject())
                throw InnertubeException("[BrowseHome] tabRenderer not found");

            if (const QJsonValue richGrid = tabRenderer["richGridRenderer"]; richGrid.isObject())
            {
                contents = richGrid["contents"].toArray();
            }
            else if (const QJsonValue sectionList = tabRenderer["sectionListRenderer"]; sectionList.isObject())
            {
                contents = sectionList["contents"].toArray();
                if (const QJsonValue continuations = sectionList["continuations"]; continuations.isArray())
                    continuationToken = continuations[0]["nextContinuationData"]["continuation"].toString();
            }
            else
            {
                throw InnertubeException("[BrowseHome] Could not find richGridRenderer or sectionListRenderer in tabRenderer");
            }
        }
        else if (const QJsonValue onResponseReceivedValue = data["onResponseReceivedActions"]; onResponseReceivedValue.isArray())
        {
            const QJsonArray onResponseReceivedActions = onResponseReceivedValue.toArray();
            // this can just happen sometimes, so will only be minor
            if (onResponseReceivedActions.isEmpty())
                throw InnertubeException("[BrowseHome] Continuation has no actions", InnertubeException::Severity::Minor);

            const QJsonValue appendItemsAction = onResponseReceivedActions[0]["appendContinuationItemsAction"];
            // now this shouldn't just happen, so will not be minor
            if (!appendItemsAction.isObject())
                throw InnertubeException("[BrowseHome] Continuation has no appendContinuationItemsAction");

            contents = appendItemsAction["continuationItems"].toArray();
        }
        else
        {
            throw InnertubeException("[BrowseHome] Failed to find any content");
        }

        for (const QJsonValue& v : std::as_const(contents))
        {
            if (const QJsonValue lockupViewModel = v["lockupViewModel"]; lockupViewModel.isObject())
            {
                response.contents.append(InnertubeObjects::LockupViewModel(lockupViewModel));
            }
            else if (const QJsonValue richItem = v["richItemRenderer"]; richItem.isObject())
            {
                if (const QJsonValue video = richItem["content"]["videoRenderer"]; video.isObject())
                    response.contents.append(InnertubeObjects::Video(video));
            }
            else if (const QJsonValue richSection = v["richSectionRenderer"]; richSection.isObject())
            {
                if (const QJsonValue richShelf = richSection["content"]["richShelfRenderer"]; richShelf.isObject())
                {
                    response.contents.append(InnertubeObjects::RichVideoShelf(
                        richShelf, { "shortsLockupViewModel", "videoRenderer" }));
                }
            }
            else if (const QJsonValue shelf = v["shelfRenderer"]; shelf.isObject())
            {
                if (const QJsonValue horizontalList = shelf["content"]["horizontalListRenderer"]; horizontalList.isObject())
                {
                    response.contents.append(InnertubeObjects::HorizontalVideoShelf(shelf,
                        InnertubeObjects::HorizontalList<InnertubeObjects::Video>(horizontalList, "gridVideoRenderer")));
                }
            }
            else if (const QJsonValue continuation = v["continuationItemRenderer"]; continuation.isObject())
            {
                continuationToken = continuation["continuationEndpoint"]["continuationCommand"]["token"].toString();
            }
        }
    }
}
