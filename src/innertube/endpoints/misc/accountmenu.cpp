#include "accountmenu.h"
#include "innertube/innertubeexception.h"
#include "innertube/itc-objects/innertubecontext.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    AccountMenu::AccountMenu(const InnertubeContext* context, const InnertubeAuthStore* authStore)
    {
        const QJsonValue data = get(context, authStore, QJsonObject {
            { "context", context->toJson() },
            { "deviceTheme", "DEVICE_THEME_SUPPORTED" },
            { "userInterfaceTheme", context->client.userInterfaceTheme }
        });

        const QJsonValue multiPageMenuRenderer = data["actions"][0]["openPopupAction"]["popup"]["multiPageMenuRenderer"];
        if (!multiPageMenuRenderer.isObject())
            throw InnertubeException("[AccountMenu] multiPageMenuRenderer not found");

        response.header = InnertubeObjects::ActiveAccountHeader(multiPageMenuRenderer["header"]["activeAccountHeaderRenderer"]);
        response.style = multiPageMenuRenderer["style"].toString();

        const QJsonArray sections = multiPageMenuRenderer["sections"].toArray();
        for (const QJsonValue& v : sections)
        {
            QList<InnertubeObjects::CompactLink> items;

            const QJsonArray itemsJson = v["multiPageMenuSectionRenderer"]["items"].toArray();
            for (const QJsonValue& v2 : itemsJson)
                items.append(InnertubeObjects::CompactLink(v2["compactLinkRenderer"]));

            response.sections.append(items);
        }
    }
}
