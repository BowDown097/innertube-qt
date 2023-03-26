#ifndef INNERTUBE_TPP
#define INNERTUBE_TPP
#include <QTimer>

template<typename T> requires std::derived_from<T, InnertubeEndpoints::BaseEndpoint> && (!std::same_as<T, InnertubeEndpoints::Subscribe>)
InnertubeReply* InnerTube::get(const QString& data, const QString& continuationToken, const QString& params)
{
    InnertubeReply* reply = new InnertubeReply;
    QTimer::singleShot(0, reply, [this, reply, data, continuationToken, params]
    {
        try
        {
            T endpoint = getBlocking<T>(data, continuationToken, params);
            emit reply->finished(endpoint);
        }
        catch (const InnertubeException& ie)
        {
            emit reply->exception(ie);
        }
    });
    return reply;
}

template<typename T> requires std::derived_from<T, InnertubeEndpoints::BaseEndpoint> && (!std::same_as<T, InnertubeEndpoints::Subscribe>)
T InnerTube::getBlocking(const QString& data, const QString& continuationToken, const QString& params)
{
    if constexpr (is_any_v<T, InnertubeEndpoints::ModifyChannelPreference, InnertubeEndpoints::Player, InnertubeEndpoints::UpdatedMetadata>)
        return T(data, _context, _authStore);
    else if constexpr (is_any_v<T, InnertubeEndpoints::BrowseHistory, InnertubeEndpoints::GetNotificationMenu, InnertubeEndpoints::Next>)
        return T(data, _context, _authStore, continuationToken);
    else if constexpr (is_any_v<T, InnertubeEndpoints::BrowseChannel, InnertubeEndpoints::Search>)
        return T(data, _context, _authStore, continuationToken, params);
    else if constexpr (is_any_v<T, InnertubeEndpoints::BrowseTrending, InnertubeEndpoints::UnseenCount>)
        return T(_context, _authStore);
    else
        return T(_context, _authStore, continuationToken);
}

#endif // INNERTUBE_TPP
