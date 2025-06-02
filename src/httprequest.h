#pragma once
#include <QMap>
#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;
class QNetworkRequest;

class HttpReply : public QObject
{
    Q_OBJECT
    friend class HttpRequest;
public:
    enum Operation
    {
        HeadOperation = 1,
        GetOperation,
        PutOperation,
        PostOperation,
        DeleteOperation,
        UnknownOperation = 0
    };

    // if you just want the QNetworkAccessManager that this uses, because it does have some extra goodies
    static QNetworkAccessManager* networkAccessManager();

    QByteArray header(const QByteArray& key) const;
    const QList<std::pair<QByteArray, QByteArray>>& headers() const;
    bool isSuccessful() const;
    QByteArray readAll() const;
    int statusCode() const;

    QByteArray requestHeader(const QByteArray& key) const { return m_requestHeaders.value(key); }
    const QMap<QByteArray, QByteArray>& requestHeaders() const { return m_requestHeaders; }
private:
    QMap<QByteArray, QByteArray> m_requestHeaders;

    explicit HttpReply(QMap<QByteArray, QByteArray>&& requestHeaders)
        : m_requestHeaders(std::move(requestHeaders)) {}
signals:
    void finished(const HttpReply& request);
};

class HttpRequest
{
public:
    HttpRequest& withDiskCache(bool usingDiskCache = true) { m_usingDiskCache = usingDiskCache; return *this; }
    HttpRequest& withHeader(const QByteArray& name, const QByteArray& value) { m_headers.insert(name, value); return *this; }
    HttpRequest& withHeaders(const QMap<QByteArray, QByteArray>& headers) { m_headers = headers; return *this; }

    HttpReply* request(const QUrl& url, HttpReply::Operation operation, const QByteArray& data = {});

    HttpReply* deleteResource(const QUrl& url) { return request(url, HttpReply::DeleteOperation); }
    HttpReply* get(const QUrl& url) { return request(url, HttpReply::GetOperation); }
    HttpReply* head(const QUrl& url) { return request(url, HttpReply::HeadOperation); }
    HttpReply* post(const QUrl& url, const QByteArray& data) { return request(url, HttpReply::PostOperation, data); }
    HttpReply* put(const QUrl& url, const QByteArray& data) { return request(url, HttpReply::PutOperation, data); }
private:
    QMap<QByteArray, QByteArray> m_headers;
    bool m_usingDiskCache{};

    QNetworkReply* networkReply(
        const QNetworkRequest& request, HttpReply::Operation operation, const QByteArray& data = {});
};
