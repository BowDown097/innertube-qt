#pragma once
#include <QJsonValue>

namespace InnertubeObjects
{
    struct DynamicLikeCountUpdateData
    {
        QString placeholderLikeCountValuesKey;
        QString updateDelayLoopId;
        int updateDelaySec{};
        QString updateStatusKey;

        DynamicLikeCountUpdateData() = default;
        explicit DynamicLikeCountUpdateData(const QJsonValue& dynamicLikeCountUpdateData)
            : placeholderLikeCountValuesKey(dynamicLikeCountUpdateData["placeholderLikeCountValuesKey"].toString()),
              updateDelayLoopId(dynamicLikeCountUpdateData["updateDelayLoopId"].toString()),
              updateDelaySec(dynamicLikeCountUpdateData["updateDelaySec"].toInt()),
              updateStatusKey(dynamicLikeCountUpdateData["updateStatusKey"].toString()) {}
    };
}
