#pragma once
#include "innertube/objects/items/button.h"

namespace InnertubeObjects
{
    struct NotificationState
    {
        int nextStateId;
        Button state;
        int stateId;

        NotificationState() = default;
        explicit NotificationState(const QJsonValue& state)
            : nextStateId(state["nextStateId"].toInt()),
              state(state["state"]["buttonRenderer"]),
              stateId(state["stateId"].toInt()) {}
    };
}
