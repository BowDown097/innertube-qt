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
        static QJsonObject _createBody(
            const InnertubeContext* context, const QString& browseId, const QString& continuationToken = "",
            const QString& query = "", const QString& params = "");

        static QJsonValue getTabRenderer(const QJsonValue& contents, const QString& name);
    };
}
