#ifndef INNERTUBEAUTHSTORE_H
#define INNERTUBEAUTHSTORE_H
#include "innertubecontext.h"
#include <QNetworkCookie>
#include <QObject>

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
    QString generateSAPISIDHash();
    QString getNecessaryLoginCookies() { return QStringLiteral("SID=%1; HSID=%2; SSID=%3; SAPISID=%4; APISID=%5").arg(sid, hsid, ssid, sapisid, apisid); }
    QJsonObject toJson() const;
    void unauthenticate(InnertubeContext*& context);
signals:
    void gotSids();
private slots:
    void cookieAdded(const QNetworkCookie& cookie);
};

#endif // INNERTUBEAUTHSTORE_H
