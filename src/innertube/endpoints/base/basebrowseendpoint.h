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
        // named "fetch" so it doesn't override BaseEndpoint::get()
        static QJsonValue fetch(const QString& browseId, const InnertubeContext* context, const InnertubeAuthStore* authStore,
                                const QString& continuationToken = "", const QString& query = "", const QString& params = "");

        static QJsonValue getTabRenderer(const QJsonValue& data, const QString& name);
    };
}
