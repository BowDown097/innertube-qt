#ifndef INNERTUBE_HPP
#define INNERTUBE_HPP
#include "endpoints/innertubeendpoints.h"
#include "itc-objects/innertubeauthstore.h"
#include <type_traits>

class InnerTube
{
public:
    static InnerTube& instance()
    {
        static InnerTube it;
        return it;
    }

    InnertubeAuthStore* authStore() const { return _authStore; }
    InnertubeContext* context() const { return _context; }
    bool hasAuthenticated() const { return authStore()->populated; }

    void authenticate() { authStore()->authenticate(*context()); }

    void createContext(const InnertubeClient& client, const InnertubeClickTracking& clickTracking = InnertubeClickTracking(),
                       const InnertubeRequestConfig& requestConfig = InnertubeRequestConfig(), const InnertubeUserConfig& userConfig = InnertubeUserConfig())
    {
        _context = new InnertubeContext(client, clickTracking, requestConfig, userConfig);
    }

    template<typename T>
    typename std::enable_if_t<std::is_base_of_v<InnertubeEndpoints::BaseEndpoint, T>, T> get(const QString& data = "")
    {
        if constexpr (std::is_same_v<T, InnertubeEndpoints::BrowseChannel> || std::is_same_v<T, InnertubeEndpoints::NextVideo>
                      || std::is_same_v<T, InnertubeEndpoints::Player>)
            return T(data, context(), easy(), authStore());
        else
            return T(context(), easy(), authStore());
    }
private:
    InnertubeAuthStore* _authStore = new InnertubeAuthStore;
    InnertubeContext* _context;
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
};

#endif // INNERTUBE_HPP
