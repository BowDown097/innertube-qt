#include "innertubeauthstore.h"
#include <QCryptographicHash>
#include <QWebEngineCookieStore>
#include <QWebEngineProfile>
#include <QWebEngineView>

void InnertubeAuthStore::authenticate(InnertubeContext*& context)
{
    QWidget authWindow;
    authWindow.setFixedSize(authWindow.size());
    authWindow.setWindowTitle("YouTube Login");
    authWindow.show();

    QWebEngineView view(&authWindow);
    view.setPage(new QWebEnginePage);
    view.setFixedSize(authWindow.size());
    view.load(QUrl("https://accounts.google.com/ServiceLogin/signinchooser?service=youtube&uilel=3&passive=true&continue=https%3A%2F%2Fwww.youtube.com%2Fsignin%3Faction_handle_signin%3Dtrue%26app%3Ddesktop%26hl%3Den%26next%3Dhttps%253A%252F%252Fwww.youtube.com%252F&hl=en&ec=65620&flowName=GlifWebSignIn&flowEntry=ServiceLogin"));
    view.show();

    QObject::connect(QWebEngineProfile::defaultProfile()->cookieStore(), &QWebEngineCookieStore::cookieAdded, this, &InnertubeAuthStore::cookieAdded);
    QEventLoop loop;
    QObject::connect(this, &InnertubeAuthStore::gotSids, &loop, &QEventLoop::quit);
    loop.exec();

    delete view.page();
    context->client.visitorData = QByteArray("\x0a" + uleb128(visitorInfo.length()) + visitorInfo.toLatin1() + "\x28" + uleb128(time(0))).toBase64().toPercentEncoding();
}

QString InnertubeAuthStore::generateSAPISIDHash()
{
    QString fmt = QStringLiteral("%1 %2 https://www.youtube.com").arg(time(NULL)).arg(sapisid);
    QString hash(QCryptographicHash::hash(fmt.toUtf8(), QCryptographicHash::Sha1).toHex());
    return QStringLiteral("SAPISIDHASH %1_%2").arg(time(NULL)).arg(hash);
}

void InnertubeAuthStore::populateFromJson(const QJsonObject& obj, InnertubeContext& context)
{
    apisid = obj["apisid"].toString();
    hsid = obj["hsid"].toString();
    sapisid = obj["sapisid"].toString();
    sid = obj["sid"].toString();
    ssid = obj["ssid"].toString();
    visitorInfo = obj["visitorInfo"].toString();

    context.client.visitorData = QByteArray("\x0a" + uleb128(visitorInfo.length()) + visitorInfo.toLatin1() + "\x28" + uleb128(time(0))).toBase64().toPercentEncoding();
    populated = true;
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

QByteArray InnertubeAuthStore::uleb128(uint64_t val)
{
    uint8_t buf[128];
    size_t i = 0;
    do
    {
        if (i < 255)
        {
            uint8_t b = val & 0x7F;
            val >>= 7;
            if (val != 0)
                b |= 0x80;
            buf[i++] = b;
        }
        else
        {
            return 0;
        }
    } while (val != 0);

    return QByteArray(reinterpret_cast<char*>(buf), i);
}

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