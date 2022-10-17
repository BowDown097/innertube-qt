#ifndef INNERTUBEAUTHSTORE_H
#define INNERTUBEAUTHSTORE_H
#include "innertubecontext.h"
#include <QNetworkCookie>
#include <QObject>

class InnertubeAuthStore : public QObject
{
    Q_OBJECT
public:
    bool populated = false;
    QString apisid, hsid, sapisid, sid, ssid, visitorInfo;

    explicit InnertubeAuthStore(QObject* parent = nullptr) : QObject(parent) {}
    void authenticate(InnertubeContext*& context);
    void authenticateFromJson(const QJsonObject& obj, InnertubeContext*& context);
    QString generateSAPISIDHash();
    QString getNecessaryLoginCookies() { return QStringLiteral("SID=%1; HSID=%2; SSID=%3; SAPISID=%4; APISID=%5").arg(sid, hsid, ssid, sapisid, apisid); }
    QJsonObject toJson() const;
private:
    QByteArray uleb128(uint64_t val);
signals:
    void gotSids();
private slots:
    void cookieAdded(const QNetworkCookie& cookie);
};

#endif // INNERTUBEAUTHSTORE_H
