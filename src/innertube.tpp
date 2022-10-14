#ifndef INNERTUBE_TPP
#define INNERTUBE_TPP

template<typename T> requires std::derived_from<T, InnertubeEndpoints::BaseEndpoint>
T InnerTube::get(const QString& data, const QString& continuationToken)
{
    if constexpr (std::is_same_v<T, InnertubeEndpoints::BrowseChannel> || std::is_same_v<T, InnertubeEndpoints::Next>
                  || std::is_same_v<T, InnertubeEndpoints::Player>)
        return T(data, context(), easy(), authStore());
    else if constexpr (std::is_same_v<T, InnertubeEndpoints::Search>)
        return T(data, context(), easy(), authStore(), continuationToken);
    else
        return T(context(), easy(), authStore(), continuationToken);
}


#endif // INNERTUBE_TPP
