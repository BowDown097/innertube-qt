#ifndef INNERTUBE_H
#define INNERTUBE_H
#include "innertube/innertubeexception.h"
#include "innertube/innertubereply.h"
#include "innertube/itc-objects/innertubeauthstore.h"
#include <QThreadPool>
#include <type_traits>

/**
 * @brief An @ref InnertubeEndpoints::BaseEndpoint "Innertube endpoint" that returns data.
 * @details The @ref InnertubeEndpoints::Like "Like", @ref InnertubeEndpoints::SendMessage "SendMessage",
 * and @ref InnertubeEndpoints::Subscribe "Subscribe" endpoints cannot be used here.<br>
 * Use their respective methods in the InnerTube class as opposed to the
 * @ref InnerTube::get "get" and @ref InnerTube::getBlocking "getBlocking" methods.
 */
template<typename T>
concept EndpointWithData = std::derived_from<T, InnertubeEndpoints::BaseEndpoint> &&
                           !std::same_as<T, InnertubeEndpoints::Like> &&
                           !std::same_as<T, InnertubeEndpoints::SendMessage> &&
                           !std::same_as<T, InnertubeEndpoints::Subscribe>;

/**
 * @brief The main attraction. Pretty much all of the interfacing with the library happens here.
 * @details ALL of the endpoint objects (and by extension, the @ref get, @ref getBlocking, @ref like, @ref sendMessage,
 * and @ref subscribe methods) are built to work with a recent version of the WEB client.
 * If not operating under these conditions, it is likely that they will be mostly or completely useless,
 * in which case you will have to use @ref InnertubeEndpoints::BaseEndpoint::get and work with the raw responses yourself.
 * But feel free to try them still if you wish.
 */
class InnerTube
{
public:
    static InnerTube& instance() { static InnerTube it; return it; }
    InnertubeAuthStore* authStore() const { return m_authStore; }
    InnertubeContext* context() const { return m_context; }

    /**
     * @brief Shorthand for @ref InnertubeAuthStore::populated.
     */
    bool hasAuthenticated() const { return m_authStore->populated(); }

#ifndef INNERTUBE_NO_WEBENGINE
    /**
     * @brief Shorthand for @ref InnertubeAuthStore::authenticate.
     */
    void authenticate() { m_authStore->authenticate(m_context); }
#endif

    /**
     * @brief Shorthand for @ref InnertubeAuthStore::authenticateFromJson.
     */
    void authenticateFromJson(const QJsonObject& obj) { m_authStore->authenticateFromJson(obj, m_context); }

    /**
     * @brief Shorthand for @ref InnertubeAuthStore::unauthenticate.
     */
    void unauthenticate() { m_authStore->unauthenticate(m_context); }

    void createContext(const InnertubeClient& client, const InnertubeClickTracking& clickTracking = InnertubeClickTracking(),
                       const InnertubeRequestConfig& requestConfig = InnertubeRequestConfig(),
                       const InnertubeUserConfig& userConfig = InnertubeUserConfig())
    { m_context = new InnertubeContext(client, clickTracking, requestConfig, userConfig); }

    /**
     * @brief Get the result of an Innertube request asynchronously.
     * @param data  Input data, for example a channel ID or search query.
     * Refer to the first parameter of the endpoint's constructor.
     * @param continuationToken  Continuation token provided by a previous Innertube response.
     * @param params  Not required for any request, but used for things like search filtering.
     * Refer to the documentation for the constructor of the endpoint objects that have this as an argument.
     * @return @ref InnertubeReply "An object" that emits signals containing the result.
     * Don't worry, it's freed when the request finishes - you don't have to manually delete it.
     */
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

    /**
     * @brief Get the result of an Innertube request synchronously.
     * @details See @ref get for parameter details.
     */
    template<EndpointWithData E>
    E getBlocking(const QString& data = "", const QString& continuationToken = "", const QString& params = "")
    {
        if constexpr (is_any_v<E, InnertubeEndpoints::GetLiveChat, InnertubeEndpoints::ModifyChannelPreference,
                               InnertubeEndpoints::Player, InnertubeEndpoints::UpdatedMetadata>)
            return E(data, m_context, m_authStore);
        else if constexpr (is_any_v<E, InnertubeEndpoints::BrowseHistory, InnertubeEndpoints::GetLiveChatReplay,
                                    InnertubeEndpoints::GetNotificationMenu, InnertubeEndpoints::Next>)
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
    void subscribe(const QStringList& channelIds, bool subscribing);
    void subscribeBlocking(const QJsonValue& endpoint, bool subscribing);
    void subscribeBlocking(const QStringList& channelIds, bool subscribing);
private:
    InnertubeAuthStore* m_authStore = new InnertubeAuthStore;
    InnertubeContext* m_context = new InnertubeContext;

    template<class T, class... U>
    static constexpr bool is_any_v = std::disjunction_v<std::is_same<T, U>...>;
};

#endif // INNERTUBE_H
