#ifndef INNERTUBE_H
#define INNERTUBE_H
#include "innertube/innertubeexception.h"
#include "innertube/innertubereply.h"
#include "innertube/itc-objects/innertubeauthstore.h"
#include <QThreadPool>
#include <type_traits>

template<typename T>
concept EndpointWithData = std::derived_from<T, InnertubeEndpoints::BaseEndpoint> &&
                           !std::same_as<T, InnertubeEndpoints::Like> &&
                           !std::same_as<T, InnertubeEndpoints::SendMessage> &&
                           !std::same_as<T, InnertubeEndpoints::Subscribe>;

class InnerTube
{
public:
    static InnerTube& instance() { static InnerTube it; return it; }
    InnertubeAuthStore* authStore() const { return m_authStore; }
    InnertubeContext* context() const { return m_context; }
    bool hasAuthenticated() const { return m_authStore->populated; }
    void authenticate() { m_authStore->authenticate(m_context); }
    void authenticateFromJson(const QJsonObject& obj) { m_authStore->authenticateFromJson(obj, m_context); }
    void unauthenticate() { m_authStore->unauthenticate(m_context); }

    void createContext(const InnertubeClient& client, const InnertubeClickTracking& clickTracking = InnertubeClickTracking(),
                       const InnertubeRequestConfig& requestConfig = InnertubeRequestConfig(),
                       const InnertubeUserConfig& userConfig = InnertubeUserConfig())
    { m_context = new InnertubeContext(client, clickTracking, requestConfig, userConfig); }

    template<EndpointWithData E>
    InnertubeReply* get(const QString& data = "", const QString& continuationToken = "", const QString& params = "")
    {
        InnertubeReply* reply = new InnertubeReply;
        QThreadPool::globalInstance()->start([this, reply, data, continuationToken, params] {
            try
            {
                E endpoint = getBlocking<E>(data, continuationToken, params);
                emit reply->finished(endpoint);
            }
            catch (const InnertubeException& ie)
            {
                emit reply->exception(ie);
            }

            reply->deleteLater();
        });
        return reply;
    }

    template<EndpointWithData E>
    E getBlocking(const QString& data = "", const QString& continuationToken = "", const QString& params = "")
    {
        if constexpr (is_any_v<E, InnertubeEndpoints::GetLiveChat, InnertubeEndpoints::ModifyChannelPreference,
                               InnertubeEndpoints::Player, InnertubeEndpoints::UpdatedMetadata>)
            return E(data, m_context, m_authStore);
        else if constexpr (is_any_v<E, InnertubeEndpoints::BrowseHistory, InnertubeEndpoints::GetNotificationMenu,
                                    InnertubeEndpoints::Next>)
            return E(data, m_context, m_authStore, continuationToken);
        else if constexpr (is_any_v<E, InnertubeEndpoints::BrowseChannel, InnertubeEndpoints::Search,
                                    InnertubeEndpoints::SendMessage>)
            return E(data, m_context, m_authStore, continuationToken, params);
        else if constexpr (is_any_v<E, InnertubeEndpoints::AccountMenu, InnertubeEndpoints::BrowseTrending,
                                    InnertubeEndpoints::UnseenCount>)
            return E(m_context, m_authStore);
        else
            return E(m_context, m_authStore, continuationToken);
    }

    void like(const QJsonValue& endpoint, bool liking);
    void sendMessage(const QJsonArray& textSegments, const QString& clientMessageId, const QString& params);
    void subscribe(const QJsonValue& endpoint, bool subscribing);
private:
    InnertubeAuthStore* m_authStore = new InnertubeAuthStore;
    InnertubeContext* m_context = new InnertubeContext;

    template<class T, class... U>
    static constexpr bool is_any_v = std::disjunction_v<std::is_same<T, U>...>;
};

#endif // INNERTUBE_H
