#ifndef INNERTUBEAUTHSTORE_H
#define INNERTUBEAUTHSTORE_H
#include "innertubecontext.h"
#include <QObject>
#include <QSettings>

#ifndef INNERTUBE_NO_WEBENGINE
#include <QNetworkCookie>
#endif

class InnertubeAuthStore : public QObject
{
    Q_OBJECT
public:
    QString apisid;
    QString hsid;
    bool populated = false;
    QString sapisid;
    QString sid;
    QString ssid;
    QString visitorInfo;

    explicit InnertubeAuthStore(QObject* parent = nullptr) : QObject(parent) {}
    void authenticate(InnertubeContext*& context);
    void authenticateFromJson(const QJsonObject& obj, InnertubeContext*& context);
    void authenticateFromSettings(const QSettings& settings, InnertubeContext*& context);
    QString generateSAPISIDHash();
    QString getNecessaryLoginCookies() { return QStringLiteral("SID=%1; HSID=%2; SSID=%3; SAPISID=%4; APISID=%5").arg(sid, hsid, ssid, sapisid, apisid); }
    QJsonObject toJson() const;
    void writeToSettings(QSettings& settings);
    void unauthenticate(InnertubeContext*& context);
signals:
    void gotSIDs();
#ifndef INNERTUBE_NO_WEBENGINE
private slots:
    void cookieAdded(const QNetworkCookie& cookie);
#endif
};

#endif // INNERTUBEAUTHSTORE_H
