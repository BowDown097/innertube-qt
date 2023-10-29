#ifndef ACTIVEACCOUNTHEADER_H
#define ACTIVEACCOUNTHEADER_H
#include "innertube/objects/genericthumbnail.h"

namespace InnertubeObjects
{
    class ActiveAccountHeader
    {
    public:
        QString accountName;
        QList<GenericThumbnail> accountPhotos;
        QString channelHandle;
        QJsonValue manageAccountEndpoint;
        QJsonValue settingsEndpoint;

        ActiveAccountHeader() = default;
        explicit ActiveAccountHeader(const QJsonValue& activeAccountHeaderRenderer);
    };
}

#endif // ACTIVEACCOUNTHEADER_H
