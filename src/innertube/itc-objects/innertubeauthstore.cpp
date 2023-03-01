#include "innertubeauthstore.h"
#include "protobuf/simpleprotobuf.h"
#include <QCryptographicHash>

#ifndef NO_WEBENGINE
#include <QEventLoop>
#include <QWebEngineCookieStore>
#include <QWebEngineProfile>
#include <QWebEngineView>
#else
#include "settingsstore.h"
#include <QMessageBox>
#endif

void InnertubeAuthStore::authenticate(InnertubeContext*& context)
{
#ifndef NO_WEBENGINE
    QWidget authWindow;
    authWindow.setFixedSize(authWindow.size());
    authWindow.setWindowTitle("YouTube Login");
    authWindow.show();

    QWebEngineView view(&authWindow);
    view.setPage(new QWebEnginePage);
    view.setFixedSize(authWindow.size());
    view.load(QUrl("https://accounts.google.com/ServiceLogin/signinchooser?service=youtube&uilel=3&passive=true&continue=https%3A%2F%2Fwww.youtube.com%2Fsignin%3Faction_handle_signin%3Dtrue%26app%3Ddesktop%26hl%3Den%26next%3Dhttps%253A%252F%252Fwww.youtube.com%252F&hl=en&ec=65620&flowName=GlifWebSignIn&flowEntry=ServiceLogin"));
    view.show();

    connect(QWebEngineProfile::defaultProfile()->cookieStore(), &QWebEngineCookieStore::cookieAdded, this, &InnertubeAuthStore::cookieAdded);

    QEventLoop loop;
    connect(this, &InnertubeAuthStore::gotSids, &loop, &QEventLoop::quit);
    loop.exec();

    delete view.page();
    context->client.visitorData = SimpleProtobuf::padded(visitorInfo);
#else
    QMessageBox::StandardButton box = QMessageBox::information(nullptr, "YouTube Login",
        QStringLiteral("Could not bring up the YouTube login page because the Qt web engine is not available.\n") +
        QStringLiteral("You will need to provide authentication credentials manually to log in.\n") +
        QStringLiteral("For info on how to do this, see https://github.com/BowDown097/innertube-qt/wiki/Manually-getting-login-credentials."));
    if (box != QMessageBox::StandardButton::Ok)
        return;

    QSettings store(SettingsStore::configPath.filePath("store.ini"), QSettings::IniFormat);
    authenticateFromSettings(store, context);
    if (!populated)
    {
        QMessageBox::information(nullptr, "Not Logged In",
            QStringLiteral("You didn't provide authentication credentials or the credentials you provided weren't accepted.\n") +
            QStringLiteral("If you provided credentials, please check them (refer back to the previously linked guide?) and try again."));
        return;
    }

    SettingsStore::instance().restoreLogin = true;
    SettingsStore::instance().saveToSettingsFile();
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
    apisid = "";
    hsid = "";
    populated = false;
    sapisid = "";
    sid = "";
    ssid = "";
    visitorInfo = "";
    context->client.visitorData = "";
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

#ifndef NO_WEBENGINE
void InnertubeAuthStore::cookieAdded(const QNetworkCookie& cookie)
{
    if (cookie.name() == "APISID")
        apisid = cookie.value();
    if (cookie.name() == "HSID")
        hsid = cookie.value();
    if (cookie.name() == "SAPISID")
        sapisid = cookie.value();
    if (cookie.name() == "SID")
        sid = cookie.value();
    if (cookie.name() == "SSID")
        ssid = cookie.value();
    if (cookie.name() == "VISITOR_INFO1_LIVE")
        visitorInfo = cookie.value();

    if (!apisid.isEmpty() && !hsid.isEmpty() && !sapisid.isEmpty() && !sid.isEmpty() && !ssid.isEmpty() && !visitorInfo.isEmpty())
    {
        populated = true;
        emit gotSids();
    }
}
#endif
