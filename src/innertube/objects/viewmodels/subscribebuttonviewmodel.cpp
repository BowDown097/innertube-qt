#include "subscribebuttonviewmodel.h"

namespace InnertubeObjects
{
    bool SubscribeButtonViewModel::isSubscribed(const QList<EntityMutation>& mutations) const
    {
        return std::ranges::any_of(mutations, [this](const EntityMutation& m) {
            return m.entityKey == stateEntityStoreKey && m.payload["subscriptionStateEntity"]["subscribed"].toBool();
        });
    }
}
