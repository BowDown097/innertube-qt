#pragma once
#include "innertubecontext.h"
#include <QObject>
#include <wobjectimpl.h>

#ifndef INNERTUBE_NO_WEBENGINE
#include <QNetworkCookie>
W_REGISTER_ARGTYPE(QNetworkCookie)
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

    explicit InnertubeAuthStore(QObject* parent = nullptr) : QObject(parent) {}

#ifndef INNERTUBE_NO_WEBENGINE
    /**
     * @brief Opens up a browser window on YouTube's login page that captures the necessary credentials.
     * @param context  @ref InnertubeContext to write visitor data to (encoded version of @ref visitorInfo).
     */
    void authenticate(InnertubeContext*& context);
#endif

    /**
     * @brief Store authentication credentials from JSON data returned by @ref toJson.
     * @param context  @ref InnertubeContext to write visitor data to (encoded version of @ref visitorInfo).
     */
    void authenticateFromJson(const QJsonObject& obj, InnertubeContext*& context);

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
    QString generateSAPISIDHash();

    /**
     * @return The authentication credentials as a JSON object to be used with @ref authenticateFromJson.
     */
    QJsonObject toJson() const;

    void authenticateSuccess() W_SIGNAL(authenticateSuccess)
#ifndef INNERTUBE_NO_WEBENGINE
private:
    void cookieAdded(const QNetworkCookie& cookie); W_SLOT(cookieAdded)
#endif
};

W_OBJECT_IMPL_INLINE(InnertubeAuthStore)
