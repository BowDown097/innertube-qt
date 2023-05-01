#ifndef SENDMESSAGE_H
#define SENDMESSAGE_H
#include "innertube/endpoints/base/baseendpoint.h"

namespace InnertubeEndpoints
{
    class SendMessage : public BaseEndpoint
    {
        friend class ::InnerTube;
    private:
        SendMessage(const QString& message, InnertubeContext* context, InnertubeAuthStore* authStore, const QString& clientMessageId,
                    const QString& params);
    };
}

#endif // SENDMESSAGE_H
