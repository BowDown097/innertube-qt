#include "subscribebuttonviewmodel.h"

namespace InnertubeObjects
{
    bool SubscribeButtonViewModel::isSubscribed(const QList<InnertubeObjects::EntityMutation>& mutations) const
    {
        return std::ranges::any_of(mutations, [this](const InnertubeObjects::EntityMutation& m) {
            return m.entityKey == stateEntityStoreKey && m.payload["subscriptionStateEntity"]["subscribed"].toBool();
        });
    }
}
