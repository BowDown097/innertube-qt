#ifndef INNERTUBE_TPP
#define INNERTUBE_TPP

template<typename T> requires std::derived_from<T, InnertubeEndpoints::BaseEndpoint>
T InnerTube::get(const QString& data, const QString& continuationToken)
{
    if constexpr (std::is_same_v<T, InnertubeEndpoints::BrowseChannel> || std::is_same_v<T, InnertubeEndpoints::Player>)
        return T(data, _context, easy(), _authStore);
    else if constexpr (std::is_same_v<T, InnertubeEndpoints::Search> || std::is_same_v<T, InnertubeEndpoints::Next>)
        return T(data, _context, easy(), _authStore, continuationToken);
    else
        return T(_context, easy(), _authStore, continuationToken);
}


#endif // INNERTUBE_TPP
