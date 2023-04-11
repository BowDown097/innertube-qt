#include "innertubeauthstore.h"
#include "protobuf/simpleprotobuf.h"
#include <QCryptographicHash>

#ifndef INNERTUBE_NO_WEBENGINE
#include <QEventLoop>
#include <QWebEngineCookieStore>
#include <QWebEngineProfile>
#include <QWebEngineView>
#endif

void InnertubeAuthStore::authenticate(InnertubeContext*& context)
{
#ifndef INNERTUBE_NO_WEBENGINE
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

    QEventLoop loop;
    connect(this, &InnertubeAuthStore::gotSIDs, &loop, &QEventLoop::quit);
    loop.exec();

    authWindow->deleteLater();
    context->client.visitorData = SimpleProtobuf::padded(visitorInfo);
#endif
}

void InnertubeAuthStore::authenticateFromJson(const QJsonObject& obj, InnertubeContext*& context)
{
    apisid = obj["apisid"].toString();
    hsid = obj["hsid"].toString();
    sapisid = obj["sapisid"].toString();
    sid = obj["sid"].toString();
    ssid = obj["ssid"].toString();
    visitorInfo = obj["visitorInfo"].toString();
    context->client.visitorData = SimpleProtobuf::padded(visitorInfo);

    if (!apisid.isEmpty() && !hsid.isEmpty() && !sapisid.isEmpty() && !sid.isEmpty() && !ssid.isEmpty() && !visitorInfo.isEmpty())
        populated = true;
}

void InnertubeAuthStore::authenticateFromSettings(const QSettings& settings, InnertubeContext*& context)
{
    apisid = settings.value("apisid").toString();
    hsid = settings.value("hsid").toString();
    sapisid = settings.value("sapisid").toString();
    sid = settings.value("sid").toString();
    ssid = settings.value("ssid").toString();
    visitorInfo = settings.value("visitorInfo").toString();
    context->client.visitorData = SimpleProtobuf::padded(visitorInfo);

    if (!apisid.isEmpty() && !hsid.isEmpty() && !sapisid.isEmpty() && !sid.isEmpty() && !ssid.isEmpty() && !visitorInfo.isEmpty())
        populated = true;
}

QString InnertubeAuthStore::generateSAPISIDHash()
{
    QString fmt = QStringLiteral("%1 %2 https://www.youtube.com").arg(time(NULL)).arg(sapisid);
    QString hash(QCryptographicHash::hash(fmt.toUtf8(), QCryptographicHash::Sha1).toHex());
    return QStringLiteral("SAPISIDHASH %1_%2").arg(time(NULL)).arg(hash);
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
    populated = false;
    sapisid.clear();
    sid.clear();
    ssid.clear();
    visitorInfo.clear();
    context->client.visitorData.clear();
}

void InnertubeAuthStore::writeToSettings(QSettings& settings)
{
    settings.setValue("apisid", apisid);
    settings.setValue("hsid", hsid);
    settings.setValue("sapisid", sapisid);
    settings.setValue("sid", sid);
    settings.setValue("ssid", ssid);
    settings.setValue("visitorInfo", visitorInfo);
}

#ifndef INNERTUBE_NO_WEBENGINE
void InnertubeAuthStore::cookieAdded(const QNetworkCookie& cookie)
{
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

    if (!apisid.isEmpty() && !hsid.isEmpty() && !sapisid.isEmpty() && !sid.isEmpty() && !ssid.isEmpty() && !visitorInfo.isEmpty())
    {
        populated = true;
        emit gotSIDs();
    }
}
#endif
