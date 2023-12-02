#ifndef DYNAMICLIKECOUNTUPDATEDATA_H
#define DYNAMICLIKECOUNTUPDATEDATA_H
#include <QJsonValue>

namespace InnertubeObjects
{
    class DynamicLikeCountUpdateData
    {
    public:
        QString placeholderLikeCountValuesKey;
        QString updateDelayLoopId;
        int updateDelaySec;
        QString updateStatusKey;

        DynamicLikeCountUpdateData() = default;
        explicit DynamicLikeCountUpdateData(const QJsonValue& dynamicLikeCountUpdateData)
            : placeholderLikeCountValuesKey(dynamicLikeCountUpdateData["placeholderLikeCountValuesKey"].toString()),
              updateDelayLoopId(dynamicLikeCountUpdateData["updateDelayLoopId"].toString()),
              updateDelaySec(dynamicLikeCountUpdateData["updateDelaySec"].toInt()),
              updateStatusKey(dynamicLikeCountUpdateData["updateStatusKey"].toString()) {}
    };
}

#endif // DYNAMICLIKECOUNTUPDATEDATA_H
