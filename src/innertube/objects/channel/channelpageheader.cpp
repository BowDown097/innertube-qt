#include "channelpageheader.h"
#include <ranges>

namespace InnertubeObjects
{
    const SubscribeButtonViewModel* ChannelPageHeader::findSubscribeButton() const
    {
        auto flatActions = actions.actionsRows
            | std::views::transform([](const auto& list) { return list.items; })
            | std::views::join;

        for (const auto& action : flatActions)
            if (const SubscribeButtonViewModel* subscribeButton = std::get_if<SubscribeButtonViewModel>(&action))
                return subscribeButton;

        return nullptr;
    }
}
