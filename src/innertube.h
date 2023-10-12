#ifndef INNERTUBE_H
#define INNERTUBE_H
#include "innertube/innertubeexception.h"
#include "innertube/innertubereply.h"
#include "innertube/itc-objects/innertubeauthstore.h"
#include <QTimer>
#include <type_traits>

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

    template<typename T> requires std::derived_from<T, InnertubeEndpoints::BaseEndpoint> && (!std::same_as<T, InnertubeEndpoints::Subscribe>)
    InnertubeReply* get(const QString& data = "", const QString& continuationToken = "", const QString& params = "")
    {
        InnertubeReply* reply = new InnertubeReply;
        QTimer::singleShot(0, reply, [this, reply, data, continuationToken, params] {
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
    T getBlocking(const QString& data = "", const QString& continuationToken = "", const QString& params = "")
    {
        if constexpr (is_any_v<T, InnertubeEndpoints::GetLiveChat, InnertubeEndpoints::ModifyChannelPreference,
                               InnertubeEndpoints::Player, InnertubeEndpoints::UpdatedMetadata>)
            return T(data, m_context, m_authStore);
        else if constexpr (is_any_v<T, InnertubeEndpoints::BrowseHistory, InnertubeEndpoints::GetNotificationMenu,
                                    InnertubeEndpoints::Next>)
            return T(data, m_context, m_authStore, continuationToken);
        else if constexpr (is_any_v<T, InnertubeEndpoints::BrowseChannel, InnertubeEndpoints::Search,
                                    InnertubeEndpoints::SendMessage>)
            return T(data, m_context, m_authStore, continuationToken, params);
        else if constexpr (is_any_v<T, InnertubeEndpoints::AccountMenu, InnertubeEndpoints::BrowseTrending,
                                    InnertubeEndpoints::UnseenCount>)
            return T(m_context, m_authStore);
        else
            return T(m_context, m_authStore, continuationToken);
    }

    void like(const QJsonValue& endpoint, bool liking);
    void sendMessage(const QJsonArray& textSegments, const QString& clientMessageId, const QString& params);
    void subscribe(const QJsonValue& endpoint, bool subscribing);
private:
    InnertubeAuthStore* m_authStore = new InnertubeAuthStore;
    InnertubeContext* m_context = new InnertubeContext;

    template<class _Tp, class... _Up>
    static constexpr bool is_any_v = std::disjunction_v<std::is_same<_Tp, _Up>...>;
};

#endif // INNERTUBE_H
