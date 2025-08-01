#include "innertubeauthstore.h"
#include "protobuf/protobufcompiler.h"
#include <QCryptographicHash>

#ifndef INNERTUBE_NO_WEBENGINE
#include <QWebEngineCookieStore>
#include <QWebEngineProfile>
#include <QWebEngineView>

// for some users, the VISITOR_INFO1_LIVE cookie doesn't get captured for some reason.
// this should work as a backup in case that happens. sadly only works on Qt 6.5+ :(
# if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
void AuthStoreRequestInterceptor::interceptRequest(QWebEngineUrlRequestInfo& info)
{
    if (!visitorIdFound)
    {
        QHash<QByteArray, QByteArray> headers = info.httpHeaders();
        if (auto it = headers.find("X-Goog-Visitor-Id"); it != headers.end())
        {
            emit foundVisitorId(it.value());
            visitorIdFound = true;
        }
    }
}
# endif

void InnertubeAuthStore::authenticate(InnertubeContext*& context)
{
    QWidget* authWindow = new QWidget;
    authWindow->setFixedSize(authWindow->size());
    authWindow->setWindowTitle("YouTube Login");
    authWindow->show();

    QWebEngineView* view = new QWebEngineView(authWindow);
    view->setFixedSize(authWindow->size());

    QWebEngineProfile* profile = new QWebEngineProfile(view);
# if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
    profile->setUrlRequestInterceptor(m_interceptor);
# endif

    QWebEnginePage* page = new QWebEnginePage(profile, view);
    view->setPage(page);

    view->load(QUrl("https://accounts.google.com/ServiceLogin/signinchooser?service=youtube&uilel=3&passive=true&continue=https%3A%2F%2Fwww.youtube.com%2Fsignin%3Faction_handle_signin%3Dtrue%26app%3Ddesktop%26hl%3Den%26next%3Dhttps%253A%252F%252Fwww.youtube.com%252F&hl=en&ec=65620&flowName=GlifWebSignIn&flowEntry=ServiceLogin"));
    view->show();

    connect(profile->cookieStore(), &QWebEngineCookieStore::cookieAdded, this, &InnertubeAuthStore::cookieAdded);
# if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
    connect(m_interceptor, &AuthStoreRequestInterceptor::foundVisitorId, this, &InnertubeAuthStore::interceptorFoundVisitorId);
# endif
    connect(this, &InnertubeAuthStore::authenticateSuccess, this, [this, authWindow, context] {
        authWindow->deleteLater();
        context->client.visitorData = visitorInfo;
    });
}

void InnertubeAuthStore::cookieAdded(const QNetworkCookie& cookie)
{
    if (populated() || cookie.domain() != ".youtube.com")
        return;

    qDebug().noquote().nospace() << "New cookie: " << cookie.name() << "=" << cookie.value();

    if (cookie.name() == "APISID")
        apisid = cookie.value();
    else if (cookie.name() == "HSID")
        hsid = cookie.value();
    else if (cookie.name() == "SAPISID")
        sapisid = cookie.value();
    else if (cookie.name() == "SID")
        sid = cookie.value();
    else if (cookie.name() == "SSID")
        ssid = cookie.value();
    else if (cookie.name() == "VISITOR_INFO1_LIVE")
        visitorInfo = ProtobufCompiler::padded(cookie.value());

    if (populated())
        emit authenticateSuccess();
}

# if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
void InnertubeAuthStore::interceptorFoundVisitorId(const QString& visitorId)
{
    qDebug().noquote().nospace() << "Found visitor ID through interceptor: " << visitorId;
    visitorInfo = visitorId;
    if (populated())
        emit authenticateSuccess();
}
# endif
#endif

QString InnertubeAuthStore::generateSAPISIDHash() const
{
    QString fmt = QStringLiteral("%1 %2 https://www.youtube.com").arg(time(NULL)).arg(sapisid);
    QString hash = QCryptographicHash::hash(fmt.toUtf8(), QCryptographicHash::Sha1).toHex();
    return QStringLiteral("SAPISIDHASH %1_%2").arg(time(NULL)).arg(hash);
}

bool InnertubeAuthStore::populated() const
{
    return !(apisid.isEmpty() || hsid.isEmpty() || sapisid.isEmpty() || sid.isEmpty() || ssid.isEmpty() || visitorInfo.isEmpty());
}

QString InnertubeAuthStore::toCookieString() const
{
    return QStringLiteral("SID=%1; HSID=%2; SSID=%3; APISID=%4; SAPISID=%5")
        .arg(sid, hsid, ssid, apisid, sapisid);
}

void InnertubeAuthStore::unauthenticate(InnertubeContext*& context)
{
    apisid.clear();
    hsid.clear();
    sapisid.clear();
    sid.clear();
    ssid.clear();
    visitorInfo.clear();
    context->client.visitorData.clear();
}
