#pragma once
#include "innertubecontext.h"
#include <wobjectimpl.h>

#ifndef INNERTUBE_NO_WEBENGINE
#include <QNetworkCookie>
W_REGISTER_ARGTYPE(QNetworkCookie)

# if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
# include <QWebEngineUrlRequestInterceptor>
class AuthStoreRequestInterceptor : public QWebEngineUrlRequestInterceptor
{
    W_OBJECT(AuthStoreRequestInterceptor)
public:
    explicit AuthStoreRequestInterceptor(QObject* parent = nullptr) : QWebEngineUrlRequestInterceptor(parent) {}
    void interceptRequest(QWebEngineUrlRequestInfo& info) override;
    void foundVisitorId(const QString& visitorId) W_SIGNAL(foundVisitorId, visitorId)
private:
    bool visitorIdFound{};
};

W_OBJECT_IMPL_INLINE(AuthStoreRequestInterceptor)
# endif
#endif

/**
 * @brief Stores YouTube authentication credentials.
 */
class InnertubeAuthStore : public QObject
{
    W_OBJECT(InnertubeAuthStore)
public:
    QString apisid;
    QString hsid;
    QString sapisid;
    QString sid;
    QString ssid;
    QString visitorInfo;

    explicit InnertubeAuthStore(QObject* parent = nullptr)
        : QObject(parent)
#ifndef INNERTUBE_NO_WEBENGINE
# if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
        , m_interceptor(new AuthStoreRequestInterceptor(this))
# endif
#endif
        {}

#ifndef INNERTUBE_NO_WEBENGINE
    /**
     * @brief Opens up a browser window on YouTube's login page that captures the necessary credentials.
     * @param context  @ref InnertubeContext to write visitor data to (encoded version of @ref visitorInfo).
     */
    void authenticate(InnertubeContext*& context);
#endif

    /**
     * @brief Clear all authentication credentials.
     * @param context  @ref InnertubeContext to clear visitor data from (encoded version of @ref visitorInfo).
     */
    void unauthenticate(InnertubeContext*& context);

    /**
     * @return If all credentials have been captured (all class members have a value).
     */
    bool populated() const;

    /**
     * @return The authentication credentials as a string to be passed as the Cookie header in a web request.
     */
    QString toCookieString() const;

    /**
     * @return A hashed version of the @ref sapisid "SAPISID" to be passed as the Authentication header in a web request.
     */
    QString generateSAPISIDHash() const;

    void authenticateSuccess() W_SIGNAL(authenticateSuccess)
#ifndef INNERTUBE_NO_WEBENGINE
# if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
    void interceptorFoundVisitorId(const QString& visitorId); W_SLOT(interceptorFoundVisitorId)
private:
    AuthStoreRequestInterceptor* m_interceptor;
# else
private:
# endif
    void cookieAdded(const QNetworkCookie& cookie); W_SLOT(cookieAdded)
#endif
};

W_OBJECT_IMPL_INLINE(InnertubeAuthStore)
