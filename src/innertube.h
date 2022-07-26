#ifndef INNERTUBE_H
#define INNERTUBE_H
#include "innertube/innertubeexception.h"
#include "innertube/endpoints/innertubeendpoints.h"
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
    void unauthenticate() { _authStore->unauthenticate(_context); }

    void createContext(const InnertubeClient& client, const InnertubeClickTracking& clickTracking = InnertubeClickTracking(),
                       const InnertubeRequestConfig& requestConfig = InnertubeRequestConfig(),
                       const InnertubeUserConfig& userConfig = InnertubeUserConfig())
    { _context = new InnertubeContext(client, clickTracking, requestConfig, userConfig); }

    template<typename T> requires std::derived_from<T, InnertubeEndpoints::BaseEndpoint>
    T get(const QString& data = "", const QString& continuationToken = "", const QString& params = "");
private:
    InnertubeAuthStore* _authStore = new InnertubeAuthStore;
    InnertubeContext* _context = new InnertubeContext;
    static CurlEasy* easy() {
        static thread_local CurlEasy* e = [] {
            CurlEasy* e = new CurlEasy;
            e->set(CURLOPT_CONNECTTIMEOUT_MS, 10000L);
            e->set(CURLOPT_FAILONERROR, 1L);
            e->set(CURLOPT_FOLLOWLOCATION, true);
            return e;
        }();
        return e;
    }

    template<class _Tp, class... _Up>
    static constexpr bool is_any_v = std::disjunction_v<std::is_same<_Tp, _Up>...>;
};

#include "innertube.tpp"

#endif // INNERTUBE_H
