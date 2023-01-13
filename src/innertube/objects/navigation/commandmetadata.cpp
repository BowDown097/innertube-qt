#include "commandmetadata.h"
#include <QJsonObject>

namespace InnertubeObjects
{
    CommandMetadata::CommandMetadata(const QJsonValue& commandMetadata)
    {
        const QJsonObject metadataObj = commandMetadata.toObject();
        QJsonObject::const_iterator cbegin = metadataObj.constBegin();
        if (cbegin == metadataObj.constEnd())
            return;

        const QJsonValue& metadata = *cbegin;
        apiUrl = metadata["apiUrl"].toString();
        rootVe = metadata["rootVe"].toInt();
        url = metadata["url"].toString();
        webPageType = metadata["webPageType"].toString();
    }
}
