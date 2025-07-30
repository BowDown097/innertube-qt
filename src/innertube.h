#pragma once
#include "innertube/innertubeexception.h"
#include "innertube/innertubereply.h"
#include "innertube/itc-objects/innertubeauthstore.h"
#include <QEventLoop>
#include <QFutureWatcher>
#include <nonstd/expected.hpp>

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
    InnerTube(QObject* parent = nullptr)
        : m_authStore(new InnertubeAuthStore(this)), QObject(parent) {}
    static InnerTube* instance() { static InnerTube _instance; return &_instance; }

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
        InnertubeReply<E>* reply = new InnertubeReply<E>;

        const QJsonObject body = E::createBody(m_context, std::forward<decltype(args)>(args)...);
        InnertubeEndpoints::prepare<E>(m_context, m_authStore, body).then([reply](QFuture<E> f) {
            try
            {
                emit reply->finished(f.result());
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
    E getBlocking(auto&&... args)
    {
        const QJsonObject body = E::createBody(m_context, std::forward<decltype(args)>(args)...);

        QFutureWatcher<E> watcher;
        watcher.setFuture(InnertubeEndpoints::prepare<E>(m_context, m_authStore, body));

        QEventLoop loop;
        connect(&watcher, &QFutureWatcher<E>::finished, &loop, &QEventLoop::quit);
        loop.exec();

        return watcher.result();
    }

    /**
     * @brief Make an Innertube request asynchronously without expecting any result object.
     * @param args  Arguments to pass in. See individual endpoint constructor parameters, excluding the
     * @ref InnertubeContext and @ref InnertubeAuthStore.
     * @return @ref InnertubeReply "An object" that emits a signal when the request has finished.
     * Don't worry, it's freed when the request finishes - you don't have to manually delete it.
     */
    template<innertube_derived_from_templated<InnertubeEndpoints::BaseEndpoint> E>
    InnertubeReply<void>* getPlain(auto&&... args)
    {
        InnertubeReply<void>* reply = new InnertubeReply<void>;

        const QJsonObject body = E::createBody(m_context, std::forward<decltype(args)>(args)...);
        E::getPlain(m_context, m_authStore, body).then([reply] {
            emit reply->finished();
            reply->deleteLater();
        });

        return reply;
    }

    /**
     * @brief Make an Innertube request synchronously without expecting any result object.
     * @details See @ref getPlain for more details.
     */
    template<innertube_derived_from_templated<InnertubeEndpoints::BaseEndpoint> E>
    void getPlainBlocking(auto&&... args)
    {
        const QJsonObject body = E::createBody(m_context, std::forward<decltype(args)>(args)...);

        QFutureWatcher<void> watcher;
        watcher.setFuture(E::getPlain(m_context, m_authStore, body));

        QEventLoop loop;
        connect(&watcher, &QFutureWatcher<void>::finished, &loop, &QEventLoop::quit);
        loop.exec();
    }

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
        addContext(body, browseIdForEndpoint<E>());

        InnertubeReply<E>* reply = new InnertubeReply<E>;
        E::get(m_context, m_authStore, body).then([reply](const QJsonValue& v) {
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
        addContext(body, browseIdForEndpoint<E>());

        QFutureWatcher<QJsonValue> watcher;
        watcher.setFuture(E::get(m_context, m_authStore, body));

        QEventLoop loop;
        connect(&watcher, &QFutureWatcher<QJsonValue>::finished, &loop, &QEventLoop::quit);
        loop.exec();

        return watcher.result();
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
    InnertubeAuthStore* m_authStore;
    InnertubeContext* m_context{};

    void addContext(QJsonObject& body, const QString& browseId);

    template<EndpointWithData E>
    QString browseIdForEndpoint()
    {
        if constexpr (std::same_as<E, InnertubeEndpoints::BrowseHistory>)
            return "FEhistory";
        else if constexpr (std::same_as<E, InnertubeEndpoints::BrowseHome>)
            return "FEwhat_to_watch";
        else if constexpr (std::same_as<E, InnertubeEndpoints::BrowseSubscriptions>)
            return "FEsubscriptions";
        else if constexpr (std::same_as<E, InnertubeEndpoints::BrowseTrending>)
            return "FEtrending";
        else
            return QString();
    }

    void subscribeImpl(const QJsonValue& endpoint, bool subscribing, bool blocking);
};
