#pragma once
#include "httpreply.h"
#include "httprequest.h"

class Http
{
public:
    static Http& instance() { static Http i; return i; }
    static const QMap<QByteArray, QByteArray>& getDefaultRequestHeaders();
    static void setDefaultReadTimeout(int timeout);

    Http();

    void addRequestHeader(const QByteArray& name, const QByteArray& value) { requestHeaders.insert(name, value); }
    QMap<QByteArray, QByteArray>& getRequestHeaders() { return requestHeaders; }
    void setRequestHeaders(const QMap<QByteArray, QByteArray>& headers) { requestHeaders = headers; }

    int getReadTimeout() { return readTimeout; }
    void setReadTimeout(int timeout) { readTimeout = timeout; }

    int getMaxRetries() const { return maxRetries; }
    void setMaxRetries(int value) { maxRetries = value; }

    QNetworkReply* networkReply(const HttpRequest& req);
    virtual HttpReply* request(const HttpRequest& req);
    HttpReply* request(const QUrl& url,
                       QNetworkAccessManager::Operation operation = QNetworkAccessManager::GetOperation,
                       const QByteArray& body = QByteArray(),
                       uint offset = 0);
    HttpReply* get(const QUrl& url);
    HttpReply* head(const QUrl& url);
    HttpReply* post(const QUrl& url, const QMap<QString, QString>& params);
    HttpReply* post(const QUrl& url, const QByteArray& body, const QByteArray& contentType);
    HttpReply* put(const QUrl& url, const QByteArray& body, const QByteArray& contentType);
    HttpReply* deleteResource(const QUrl& url);
private:
    int maxRetries{};
    int readTimeout{};
    QMap<QByteArray, QByteArray> requestHeaders;
};
