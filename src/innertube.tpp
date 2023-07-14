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
            emit reply->finished(std::move(endpoint));
        }
        catch (const InnertubeException& ie)
        {
            emit reply->exception(ie);
        }

        reply->deleteLater();
    });
    return reply;
}

template<typename T> requires std::derived_from<T, InnertubeEndpoints::BaseEndpoint> && (!std::same_as<T, InnertubeEndpoints::Subscribe>)
T InnerTube::getBlocking(const QString& data, const QString& continuationToken, const QString& params)
{
    if constexpr (is_any_v<T, InnertubeEndpoints::GetLiveChat, InnertubeEndpoints::ModifyChannelPreference, InnertubeEndpoints::Player,
                           InnertubeEndpoints::UpdatedMetadata>)
        return T(data, m_context, m_authStore);
    else if constexpr (is_any_v<T, InnertubeEndpoints::BrowseHistory, InnertubeEndpoints::GetNotificationMenu, InnertubeEndpoints::Next>)
        return T(data, m_context, m_authStore, continuationToken);
    else if constexpr (is_any_v<T, InnertubeEndpoints::BrowseChannel, InnertubeEndpoints::Search, InnertubeEndpoints::SendMessage>)
        return T(data, m_context, m_authStore, continuationToken, params);
    else if constexpr (is_any_v<T, InnertubeEndpoints::AccountMenu, InnertubeEndpoints::BrowseTrending, InnertubeEndpoints::UnseenCount>)
        return T(m_context, m_authStore);
    else
        return T(m_context, m_authStore, continuationToken);
}

#endif // INNERTUBE_TPP
