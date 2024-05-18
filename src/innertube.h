#pragma once
#include "innertube/innertubeexception.h"
#include "innertube/innertubereply.h"
#include "innertube/itc-objects/innertubeauthstore.h"
#include <mutex>
#include <QJsonDocument>
#include <QThreadPool>

/**
 * @brief The main attraction. Pretty much all of the interfacing with the library happens here.
 * @details ALL of the endpoint objects (and by extension, the @ref get, @ref getBlocking, @ref like, @ref sendMessage,
 * and @ref subscribe methods) are built to work with a recent version of the WEB client.
 * If not operating under these conditions, it is likely that they will be mostly or completely useless,
 * in which case you will have to use @ref InnertubeEndpoints::BaseEndpoint::get and work with the raw responses yourself.
 * But feel free to try them still if you wish.
 */
class InnerTube : public QObject
{
public:
    static InnerTube* instance();
    InnerTube(QObject* parent = nullptr)
        : m_authStore(new InnertubeAuthStore(this)), m_context(new InnertubeContext(this)), QObject(parent) {}

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
    { m_context = new InnertubeContext(client, clickTracking, requestConfig, userConfig, this); }

    /**
     * @brief Get the result of an Innertube request asynchronously.
     * @param args  Arguments to pass in. See individual endpoint constructor parameters, excluding the
     * @ref InnertubeContext and @ref InnertubeAuthStore.
     * @return @ref InnertubeReply "An object" that emits signals containing the result.
     * Don't worry, it's freed when the request finishes - you don't have to manually delete it.
     */
    template<EndpointWithData E>
    InnertubeReply<E>* get(auto&&... args)
    {
        InnertubeReply<E>* reply = new InnertubeReply<E>;
        QThreadPool::globalInstance()->start([this, reply, ...args = std::forward<decltype(args)>(args)]() mutable {
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
     * @brief Get the raw result of an Innertube request asynchronously.
     * @details Use this if you are not using the WEB client.
     * @param body  JSON body for the request. See the endpoint's constructor code for what to do.
     * @return @ref InnertubeReply "An object" that emits signals containing the result.
     * Specifically, you'll want to connect to finishedRaw.
     * Don't worry, it's freed when the request finishes - you don't have to manually delete it.
     */
    template<EndpointWithData E>
    InnertubeReply<E>* getRaw(const QJsonObject& body)
    {
        InnertubeReply<E>* reply = new InnertubeReply<E>;
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
    static inline InnerTube* m_instance;
    static inline std::once_flag m_onceFlag;

    InnertubeAuthStore* m_authStore;
    InnertubeContext* m_context;
};
