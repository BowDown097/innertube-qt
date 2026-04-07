#include "videoowner.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    VideoOwner::VideoOwner(const QJsonValue& videoOwnerRenderer)
        : navigationEndpoint(videoOwnerRenderer["navigationEndpoint"]),
          subscriptionButton(videoOwnerRenderer["subscriptionButton"])
    {
        if (const QJsonValue attrTitle = videoOwnerRenderer["attributedTitle"]; attrTitle.isObject())
        {
            const QJsonValue listItem = attrTitle
                ["commandRuns"][0]["onTap"]["innertubeCommand"]["showDialogCommand"]
                ["panelLoadingStrategy"]["inlineContent"]["dialogViewModel"]
                ["customContent"]["listViewModel"]["listItems"][0]["listItemViewModel"];

            subscriberCountText = InnertubeString(listItem["subtitle"]["content"].toString().section(" • ", -1));
            title = InnertubeString(listItem["title"]["content"].toString());

            const QString attachmentImage = listItem
                ["title"]["attachmentRuns"][0]["element"]["type"]["imageType"]
                ["image"]["sources"][0]["clientResource"]["imageName"].toString();
            if (!attachmentImage.isEmpty())
                badges.emplaceBack(attachmentImage);
        }
        else
        {
            subscriberCountText = InnertubeString(videoOwnerRenderer["subscriberCountText"]);
            title = InnertubeString(videoOwnerRenderer["title"]);

            const QJsonArray badgesJson = videoOwnerRenderer["badges"].toArray();
            for (const QJsonValue& v : badgesJson)
                badges.emplaceBack(v["metadataBadgeRenderer"]);
        }

        if (const QJsonValue avatarStack = videoOwnerRenderer["avatarStack"]; avatarStack.isObject())
        {
            const QString source = avatarStack
                ["avatarStackViewModel"]["avatars"][0]["avatarViewModel"]
                ["image"]["sources"][0]["url"].toString()
                .replace("=s88-", "=s176-");
            thumbnail.emplaceBack(176, source, 176);
        }
        else
        {
            const QJsonArray thumbnails = videoOwnerRenderer["thumbnail"]["thumbnails"].toArray();
            for (const QJsonValue& v : thumbnails)
                thumbnail.emplaceBack(v);
        }

        if (const QJsonValue membershipButtonJson = videoOwnerRenderer["membershipButton"]; membershipButtonJson.isObject())
            membershipButton.emplace(membershipButtonJson["timedAnimationButtonRenderer"]["buttonRenderer"]["buttonRenderer"]);
    }

    QString VideoOwner::channelId() const
    {
        if (const QJsonValue browseEndpoint = navigationEndpoint["browseEndpoint"]; browseEndpoint.isObject())
        {
            return browseEndpoint["browseId"].toString();
        }
        else if (const QJsonValue showDialog = navigationEndpoint["showDialogCommand"]; showDialog.isObject())
        {
            return showDialog["panelLoadingStrategy"]["inlineContent"]["dialogViewModel"]
                ["customContent"]["listViewModel"]["listItems"][0]
                ["listItemViewModel"]["title"]["commandRuns"][0]["onTap"]
                ["innertubeCommand"]["browseEndpoint"]["browseId"].toString();
        }

        return {};
    }
}
