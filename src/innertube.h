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
    InnertubeAuthStore* authStore() const { return _authStore; }
    InnertubeContext* context() const { return _context; }
    bool hasAuthenticated() const { return _authStore->populated; }
    void authenticate() { _authStore->authenticate(_context); }
    void authenticateFromJson(const QJsonObject& obj) { _authStore->authenticateFromJson(obj, _context); }
    void authenticateFromSettings(const QSettings& settings) { _authStore->authenticateFromSettings(settings, _context); }
    void unauthenticate() { _authStore->unauthenticate(_context); }

    void createContext(const InnertubeClient& client, const InnertubeClickTracking& clickTracking = InnertubeClickTracking(),
                       const InnertubeRequestConfig& requestConfig = InnertubeRequestConfig(),
                       const InnertubeUserConfig& userConfig = InnertubeUserConfig())
    { _context = new InnertubeContext(client, clickTracking, requestConfig, userConfig); }

    template<typename T> requires std::derived_from<T, InnertubeEndpoints::BaseEndpoint> && (!std::same_as<T, InnertubeEndpoints::Subscribe>)
    InnertubeReply* get(const QString& data = "", const QString& continuationToken = "", const QString& params = "");

    template<typename T> requires std::derived_from<T, InnertubeEndpoints::BaseEndpoint> && (!std::same_as<T, InnertubeEndpoints::Subscribe>)
    T getBlocking(const QString& data = "", const QString& continuationToken = "", const QString& params = "");

    void like(const QJsonValue& endpoint, bool liking)
    {
        if (endpoint.toObject().contains("removeLikeParams"))
        {
            InnertubeEndpoints::Like(endpoint["target"]["videoId"].toString(), endpoint["removeLikeParams"].toString(),
                liking, true, _context, _authStore);
        }
        else
        {
            InnertubeEndpoints::Like(
                endpoint["target"]["videoId"].toString(),
                liking ? endpoint["likeParams"].toString() : endpoint["dislikeParams"].toString(),
                liking, false, _context, _authStore
            );
        }
    }

    void subscribe(const QJsonValue& endpoint, bool subscribing)
    {
        QList<QString> channelIds;
        const QJsonArray channelIdsJson = endpoint["channelIds"].toArray();
        for (const QJsonValue& v : channelIdsJson)
            channelIds.append(v.toString());
        InnertubeEndpoints::Subscribe(channelIds, endpoint["params"].toString(), subscribing, _context, _authStore);
    }
private:
    InnertubeAuthStore* _authStore = new InnertubeAuthStore;
    InnertubeContext* _context = new InnertubeContext;

    template<class _Tp, class... _Up>
    static constexpr bool is_any_v = std::disjunction_v<std::is_same<_Tp, _Up>...>;
};

#include "innertube.tpp"

#endif // INNERTUBE_H
