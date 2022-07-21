#ifndef INNERTUBE_H
#define INNERTUBE_H
#include "endpoints/innertubeendpoints.h"
#include "itc-objects/innertubeauthstore.h"
#include <QtNetwork>
#include <type_traits>

class InnerTube
{
public:
    static InnerTube& instance()
    {
        static InnerTube it;
        return it;
    }

    InnertubeAuthStore* auth() { return _authStore; }
    InnertubeContext* context() { return _context; }

    void createContext(const InnertubeClient& client, const InnertubeClickTracking& clickTracking = InnertubeClickTracking(),
                       const InnertubeRequestConfig& requestConfig = InnertubeRequestConfig(), const InnertubeUserConfig& userConfig = InnertubeUserConfig())
    {
        _context = new InnertubeContext(client, clickTracking, requestConfig, userConfig);
    }

    template<typename T>
    typename std::enable_if_t<std::is_base_of_v<InnertubeEndpoints::BaseEndpoint, T>, T> get(InnertubeAuthStore* authStore = new InnertubeAuthStore, bool useShelves = false)
    {
        if constexpr (std::is_same_v<T, InnertubeEndpoints::AccountMenu>)
            return InnertubeEndpoints::AccountMenu(context(), networkAccessManager(), authStore);
        if constexpr (std::is_same_v<T, InnertubeEndpoints::Browse>)
            return InnertubeEndpoints::Browse(context(), networkAccessManager(), authStore, useShelves);
    }
private:
    InnertubeAuthStore* _authStore = new InnertubeAuthStore;
    InnertubeContext* _context;
    static QNetworkAccessManager* networkAccessManager() {
        static thread_local QNetworkAccessManager* nam = [] {
            QNetworkAccessManager* nam = new QNetworkAccessManager();
            nam->setTransferTimeout(10000);
            nam->setRedirectPolicy(QNetworkRequest::RedirectPolicy::NoLessSafeRedirectPolicy);
            return nam;
        }();
        return nam;
    }
};

#endif // INNERTUBE_H
