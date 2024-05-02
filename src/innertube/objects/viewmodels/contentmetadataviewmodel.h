#pragma once
#include <QJsonValue>

namespace InnertubeObjects
{
    struct ContentMetadataViewModel
    {
        QString delimiter;
        QList<QStringList> metadataRows;

        ContentMetadataViewModel() = default;
        explicit ContentMetadataViewModel(const QJsonValue& contentMetadataViewModel);
    };
}
