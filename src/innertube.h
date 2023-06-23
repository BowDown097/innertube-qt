#ifndef INNERTUBE_H
#define INNERTUBE_H
#include "innertube/innertubeexception.h"
#include "innertube/innertubereply.h"
#include "innertube/itc-objects/innertubeauthstore.h"
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
    void authenticateFromSettings(const QSettings& settings) { m_authStore->authenticateFromSettings(settings, m_context); }
    void unauthenticate() { m_authStore->unauthenticate(m_context); }

    void createContext(const InnertubeClient& client, const InnertubeClickTracking& clickTracking = InnertubeClickTracking(),
                       const InnertubeRequestConfig& requestConfig = InnertubeRequestConfig(),
                       const InnertubeUserConfig& userConfig = InnertubeUserConfig())
    { m_context = new InnertubeContext(client, clickTracking, requestConfig, userConfig); }

    template<typename T> requires std::derived_from<T, InnertubeEndpoints::BaseEndpoint> && (!std::same_as<T, InnertubeEndpoints::Subscribe>)
    InnertubeReply* get(const QString& data = "", const QString& continuationToken = "", const QString& params = "");

    template<typename T> requires std::derived_from<T, InnertubeEndpoints::BaseEndpoint> && (!std::same_as<T, InnertubeEndpoints::Subscribe>)
    T getBlocking(const QString& data = "", const QString& continuationToken = "", const QString& params = "");

    void like(const QJsonValue& endpoint, bool liking);
    void sendMessage(const QJsonArray& textSegments, const QString& clientMessageId, const QString& params);
    void subscribe(const QJsonValue& endpoint, bool subscribing);
private:
    InnertubeAuthStore* m_authStore = new InnertubeAuthStore;
    InnertubeContext* m_context = new InnertubeContext;

    template<class _Tp, class... _Up>
    static constexpr bool is_any_v = std::disjunction_v<std::is_same<_Tp, _Up>...>;
};

#include "innertube.tpp"

#endif // INNERTUBE_H
