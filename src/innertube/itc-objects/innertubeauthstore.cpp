#include "innertubeauthstore.h"
#include "protobuf/protobufcompiler.h"
#include <QCryptographicHash>

#ifndef INNERTUBE_NO_WEBENGINE
#include <QEventLoop>
#include <QWebEngineCookieStore>
#include <QWebEngineProfile>
#include <QWebEngineView>

void InnertubeAuthStore::authenticate(InnertubeContext*& context)
{
    QWidget* authWindow = new QWidget;
    authWindow->setFixedSize(authWindow->size());
    authWindow->setWindowTitle("YouTube Login");
    authWindow->show();

    QWebEngineView* view = new QWebEngineView(authWindow);
    view->setFixedSize(authWindow->size());

    QWebEnginePage* page = new QWebEnginePage(view);
    view->setPage(page);
    view->load(QUrl("https://accounts.google.com/ServiceLogin/signinchooser?service=youtube&uilel=3&passive=true&continue=https%3A%2F%2Fwww.youtube.com%2Fsignin%3Faction_handle_signin%3Dtrue%26app%3Ddesktop%26hl%3Den%26next%3Dhttps%253A%252F%252Fwww.youtube.com%252F&hl=en&ec=65620&flowName=GlifWebSignIn&flowEntry=ServiceLogin"));
    view->show();

    connect(QWebEngineProfile::defaultProfile()->cookieStore(), &QWebEngineCookieStore::cookieAdded, this, &InnertubeAuthStore::cookieAdded);
    connect(this, &InnertubeAuthStore::authenticateSuccess, this, [this, authWindow, context] {
        authWindow->deleteLater();
        context->client.visitorData = ProtobufCompiler::padded(visitorInfo);
    });
}

void InnertubeAuthStore::cookieAdded(const QNetworkCookie& cookie)
{
    if (populated())
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
        visitorInfo = cookie.value();

    if (populated())
        emit authenticateSuccess();
}
#endif

void InnertubeAuthStore::authenticateFromJson(const QJsonObject& obj, InnertubeContext*& context)
{
    apisid = obj["apisid"].toString();
    hsid = obj["hsid"].toString();
    sapisid = obj["sapisid"].toString();
    sid = obj["sid"].toString();
    ssid = obj["ssid"].toString();
    visitorInfo = obj["visitorInfo"].toString();
    context->client.visitorData = ProtobufCompiler::padded(visitorInfo);
}

QString InnertubeAuthStore::generateSAPISIDHash()
{
    QString fmt = QStringLiteral("%1 %2 https://www.youtube.com").arg(time(NULL)).arg(sapisid);
    QString hash(QCryptographicHash::hash(fmt.toUtf8(), QCryptographicHash::Sha1).toHex());
    return QStringLiteral("SAPISIDHASH %1_%2").arg(time(NULL)).arg(hash);
}

bool InnertubeAuthStore::populated() const
{
    return !(apisid.isEmpty() || hsid.isEmpty() || sapisid.isEmpty() || sid.isEmpty() || ssid.isEmpty() || visitorInfo.isEmpty());
}

QString InnertubeAuthStore::toCookieString() const
{
    return QStringLiteral("SID=%1; HSID=%2; SSID=%3; APISID=%4; SAPISID=%5; VISITOR_INFO1_LIVE=%6")
        .arg(sid, hsid, ssid, apisid, sapisid, visitorInfo);
}

QJsonObject InnertubeAuthStore::toJson() const
{
    return {
        { "apisid", apisid },
        { "hsid", hsid },
        { "sapisid", sapisid },
        { "sid", sid },
        { "ssid", ssid },
        { "visitorInfo", visitorInfo }
    };
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
