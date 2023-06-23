#ifndef NOTIFICATIONSTATE_H
#define NOTIFICATIONSTATE_H
#include "innertube/objects/items/button.h"

namespace InnertubeObjects
{
    class NotificationState
    {
    public:
        int nextStateId = 0;
        Button state;
        int stateId = 0;

        NotificationState() = default;
        explicit NotificationState(const QJsonValue& state)
            : nextStateId(state["nextStateId"].toInt()),
              state(state["state"]["buttonRenderer"]),
              stateId(state["stateId"].toInt()) {}
    };
}

#endif // NOTIFICATIONSTATE_H
