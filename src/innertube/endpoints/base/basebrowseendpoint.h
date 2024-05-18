#pragma once
#include "baseendpoint.h"

namespace InnertubeEndpoints
{
    /**
     * @brief The parent of all browse endpoint objects.
     * @details This doesn't really serve any purpose for the user, just a nice abstraction internally.
     */
    class BaseBrowseEndpoint : public BaseEndpoint<"browse">
    {
    protected:
        QByteArray data;
        BaseBrowseEndpoint(const QString& browseId, InnertubeContext* context, InnertubeAuthStore* authStore,
                           const QString& continuationToken = "", const QString& query = "");
        QJsonValue getTabRenderer(const QString& name) const;
    };
}
