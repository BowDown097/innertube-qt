#pragma once
#include "innertube/objects/items/listbase.h"

namespace InnertubeObjects
{
    template<typename... ActionTypes>
    struct FlexibleActionsViewModel
    {
        QList<ListBase<ActionTypes...>> actionsRows;
        int minimumRowHeight{};
        QJsonValue rendererContext;

        FlexibleActionsViewModel() = default;
        explicit FlexibleActionsViewModel(const QJsonValue& flexibleActionsViewModel,
                                          const std::array<QString, sizeof...(ActionTypes)>& actionKeys)
            : minimumRowHeight(flexibleActionsViewModel["minimumRowHeight"].toInt()),
              rendererContext(flexibleActionsViewModel["rendererContext"])
        {
            const QJsonArray actionsRowsJson = flexibleActionsViewModel["actionsRows"].toArray();
            for (const QJsonValue& row : actionsRowsJson)
                actionsRows.append(ListBase<ActionTypes...>(row, actionKeys, "actions"));
        }
    };
}
