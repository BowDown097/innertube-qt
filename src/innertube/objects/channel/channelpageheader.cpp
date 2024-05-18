#include "channelpageheader.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    ChannelPageHeader::ChannelPageHeader(const QJsonValue& pageHeaderViewModel)
        : attribution(pageHeaderViewModel["attribution"]["attributionViewModel"]),
          avatar(pageHeaderViewModel["image"]["decoratedAvatarViewModel"]["avatar"]["avatarViewModel"]["image"]["sources"]),
          banner(pageHeaderViewModel["banner"]["imageBannerViewModel"]["image"]["sources"]),
          description(pageHeaderViewModel["description"]["descriptionPreviewViewModel"], "description"),
          metadata(pageHeaderViewModel["metadata"]["contentMetadataViewModel"]),
          title(pageHeaderViewModel["title"]["dynamicTextViewModel"])
    {
        const QJsonValue actionRow = pageHeaderViewModel["actions"]["flexibleActionsViewModel"]["actionsRows"][0];
        if (QJsonValue subButtonValue = actionRow["actions"][0]["subscribeButtonViewModel"]; subButtonValue.isObject())
            subscribeButton = SubscribeButtonViewModel(subButtonValue);
        else
            subscribeButton = std::nullopt;

        const QJsonArray actionsArr = actionRow["actions"].toArray();
        if (!subscribeButton)
        {
            for (const QJsonValue& action : actionsArr)
                actions.append(InnertubeObjects::ButtonViewModel(action["buttonViewModel"]));
        }
        else if (actionsArr.size() > 1)
        {
            for (int i = 1; i < actionsArr.size(); i++)
                actions.append(InnertubeObjects::ButtonViewModel(actionsArr[i]["buttonViewModel"]));
        }
    }
}
