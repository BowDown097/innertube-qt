#ifndef INNERTUBE_TPP
#define INNERTUBE_TPP

template<typename T> requires std::derived_from<T, InnertubeEndpoints::BaseEndpoint> && (!std::same_as<T, InnertubeEndpoints::Subscribe>)
T InnerTube::get(const QString& data, const QString& continuationToken, const QString& params)
{
    if constexpr (std::is_same_v<T, InnertubeEndpoints::Player>)
        return T(data, _context, easy(), _authStore);
    else if constexpr (is_any_v<T, InnertubeEndpoints::BrowseHistory, InnertubeEndpoints::GetNotificationMenu, InnertubeEndpoints::Next>)
        return T(data, _context, easy(), _authStore, continuationToken);
    else if constexpr (is_any_v<T, InnertubeEndpoints::BrowseChannel, InnertubeEndpoints::Search>)
        return T(data, _context, easy(), _authStore, continuationToken, params);
    else if constexpr (is_any_v<T, InnertubeEndpoints::BrowseTrending, InnertubeEndpoints::UnseenCount>)
        return T(_context, easy(), _authStore);
    else
        return T(_context, easy(), _authStore, continuationToken);
}

#endif // INNERTUBE_TPP
