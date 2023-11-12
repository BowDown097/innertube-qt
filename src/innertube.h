#ifndef INNERTUBE_H
#define INNERTUBE_H
#include "innertube/innertubeexception.h"
#include "innertube/innertubereply.h"
#include "innertube/itc-objects/innertubeauthstore.h"
#include <QJsonDocument>
#include <QThreadPool>
#include <type_traits>

template<class T, class... U>
static constexpr bool innertube_is_any_v = std::disjunction_v<std::is_same<T, U>...>;

/**
 * @brief An @ref InnertubeEndpoints::BaseEndpoint "Innertube endpoint" that returns data.
 * @details The @ref InnertubeEndpoints::Like "Like", @ref InnertubeEndpoints::SendMessage "SendMessage",
 * and @ref InnertubeEndpoints::Subscribe "Subscribe" endpoints cannot be used here.<br>
 * Use their respective methods in the InnerTube class as opposed to the
 * @ref InnerTube::get "get" and @ref InnerTube::getBlocking "getBlocking" methods.
 */
template<class C>
concept EndpointWithData = requires(C c)
{
    []<InnertubeEndpoints::CompTimeStr X>(InnertubeEndpoints::BaseEndpoint<X>&){}(c);
} && !innertube_is_any_v<C, InnertubeEndpoints::Like, InnertubeEndpoints::SendMessage, InnertubeEndpoints::Subscribe>;

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
     * @param args  Arguments to pass in. See individual endpoint constructor parameters, excluding the
     * @ref InnertubeContext and @ref InnertubeAuthStore.
     * @return @ref InnertubeReply "An object" that emits signals containing the result.
     * Don't worry, it's freed when the request finishes - you don't have to manually delete it.
     */
    template<EndpointWithData E>
    InnertubeReply* get(auto&&... args)
    {
        InnertubeReply* reply = new InnertubeReply;
        QThreadPool::globalInstance()->start([this, reply, ...args = std::forward<decltype(args)>(args)] {
            try
            {
                E endpoint = getBlocking<E>(std::forward<decltype(args)>(args)...);
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
     * @details See @ref get for more details.
     */
    template<EndpointWithData E>
    E getBlocking(auto&&... args) { return E(m_context, m_authStore, std::forward<decltype(args)>(args)...); }

    /**
     * @brief Get the result of an Innertube request asynchronously.
     * @details Use this if you are not using the WEB client.
     * @param body  JSON body for the request. See the endpoint's constructor code for what to do.
     * @return @ref InnertubeReply "An object" that emits signals containing the result.
     * Specifically, you'll want to connect to finishedRaw.
     * Don't worry, it's freed when the request finishes - you don't have to manually delete it.
     */
    template<EndpointWithData E>
    InnertubeReply* getRaw(const QJsonObject& body)
    {
        InnertubeReply* reply = new InnertubeReply;
        QThreadPool::globalInstance()->start([this, reply, body] {
            QJsonValue v = getRawBlocking<E>(body);
            emit reply->finishedRaw(v);
            reply->deleteLater();
        });
        return reply;
    }

    /**
     * @brief Get the raw result of an Innertube request synchronously.
     * @details See @ref getRaw for more details.
     */
    template<EndpointWithData E>
    QJsonValue getRawBlocking(QJsonObject body)
    {
        body.insert("context", m_context->toJson());
        QByteArray data = E::get(m_context, m_authStore, body);
        return QJsonDocument::fromJson(data).object();
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
};

#endif // INNERTUBE_H
