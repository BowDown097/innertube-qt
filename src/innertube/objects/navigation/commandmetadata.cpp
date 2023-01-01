#include "commandmetadata.h"
#include <QJsonObject>

namespace InnertubeObjects
{
    CommandMetadata::CommandMetadata(const QJsonValue& commandMetadata)
    {
        QJsonObject metadataObj = commandMetadata.toObject();
        QJsonObject::iterator cbegin = metadataObj.begin();
        if (cbegin == metadataObj.end())
            return;

        QJsonValue metadata = *cbegin;
        apiUrl = metadata["apiUrl"].toString();
        rootVe = metadata["rootVe"].toInt();
        url = metadata["url"].toString();
        webPageType = metadata["webPageType"].toString();
    }
}
