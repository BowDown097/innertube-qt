#ifndef ACTIVEACCOUNTHEADER_H
#define ACTIVEACCOUNTHEADER_H
#include "innertube/objects/genericthumbnail.h"

namespace InnertubeObjects
{
    class ActiveAccountHeader
    {
    public:
        QString accountName;
        QList<GenericThumbnail> accountPhoto;
        QString channelHandle;

        ActiveAccountHeader() = default;
        explicit ActiveAccountHeader(const QJsonValue& activeAccountHeaderRenderer);
    };
}

#endif // ACTIVEACCOUNTHEADER_H
