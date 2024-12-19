#pragma once
#include "innertube/innertubeexception.h"
#include "innertube/innertubereply.h"
#include "innertube/itc-objects/innertubeauthstore.h"
#include "jsonutil.h"
#include <mutex>
#include <nonstd/expected.hpp>
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
        : m_authStore(new InnertubeAuthStore(this)), QObject(parent) {}

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

    /**
     * @brief Creates a context for this instance. Required for anything to work.
     * @param client  Required.
     * @param clickTracking  Don't touch unless if you really know what you're doing.
     * @param requestConfig  See above parameter.
     * @param userConfig  See above parameter.
     */
    void createContext(const InnertubeClient& client, const InnertubeClickTracking& clickTracking = InnertubeClickTracking(),
                       const InnertubeRequestConfig& requestConfig = InnertubeRequestConfig(),
                       const InnertubeUserConfig& userConfig = InnertubeUserConfig())
    { m_context = new InnertubeContext(client, clickTracking, requestConfig, userConfig, this); }

    /**
     * @brief createClient  Creates a client for this instance. Useful if you don't care about the
     * other parameters in @ref createContext.
     * @param args  Arguments to be passed to the constructor of InnertubeClient.
     */
    void createClient(auto&&... args)
    {
        createContext(InnertubeClient(std::forward<decltype(args)>(args)...));
    }

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
        auto argsTuple = std::make_tuple(std::forward<decltype(args)>(args)...);
        InnertubeReply<E>* reply = new InnertubeReply<E>;

        QThreadPool::globalInstance()->start([this, argsTuple = std::move(argsTuple), reply] {
            try
            {
                auto endpoint = std::apply([this](auto&&... unpacked) {
                    return getBlocking<E>(std::forward<decltype(unpacked)>(unpacked)...);
                }, argsTuple);
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
    InnertubeReply<E>* getRaw(QJsonObject body = {})
    {
        InnertubeReply<E>* reply = new InnertubeReply<E>;
        QThreadPool::globalInstance()->start([this, reply, body = std::move(body)] {
            QJsonValue v = getRawBlocking<E>(std::move(body));
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
    QJsonValue getRawBlocking(QJsonObject body = {})
    {
        // merge unique properties from context, so that properties can be overriden by the user
        if (body["context"].isObject())
        {
            QJsonObject contextObj = m_context->toJson();
            const QJsonObject bodyContext = body["context"].toObject();
            JsonUtil::deepMerge(contextObj, bodyContext);
            body["context"] = contextObj;
        }
        else
        {
            body.insert("context", m_context->toJson());
        }

        // we can automatically resolve the browseId for the browse endpoints (excl. channels)
        if constexpr (std::same_as<E, InnertubeEndpoints::BrowseHistory>)
            body.insert("browseId", "FEhistory");
        else if constexpr (std::same_as<E, InnertubeEndpoints::BrowseHome>)
            body.insert("browseId", "FEwhat_to_watch");
        else if constexpr (std::same_as<E, InnertubeEndpoints::BrowseSubscriptions>)
            body.insert("browseId", "FEsubscriptions");
        else if constexpr (std::same_as<E, InnertubeEndpoints::BrowseTrending>)
            body.insert("browseId", "FEtrending");

        return E::get(m_context, m_authStore, std::move(body));
    }

    /**
     * @brief Try to create an instance of an endpoint class.
     * @param data  JSON data to be processed
     * @return Expected value - the endpoint instance, or the exception that its constructor threw.
     */
    template<EndpointWithData E>
    static nonstd::expected<E, InnertubeException> tryCreate(const QJsonValue& data)
    {
        try
        {
            return E(data);
        }
        catch (const InnertubeException& e)
        {
            return nonstd::unexpected<InnertubeException>(e);
        }
    }

    void like(const QJsonValue& endpoint, bool liking);

    void sendMessage(const QJsonArray& textSegments, const QString& clientMessageId, const QString& params);
    void sendMessage(const QString& message, const QString& clientMessageId, const QString& params);

    void subscribe(const QJsonValue& endpoint, bool subscribing);
    void subscribe(const QStringList& channelIds, bool subscribing);
    void subscribeBlocking(const QJsonValue& endpoint, bool subscribing);
    void subscribeBlocking(const QStringList& channelIds, bool subscribing);
private:
    static inline InnerTube* m_instance;
    static inline std::once_flag m_onceFlag;

    InnertubeAuthStore* m_authStore;
    InnertubeContext* m_context{};
};
