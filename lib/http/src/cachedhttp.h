#pragma once
#include "http.h"

class LocalCache;

class CachedHttp : public Http
{
public:
    using ValidatorMap = QMap<QByteArray, std::function<bool(const HttpReply&)>>;
    explicit CachedHttp(Http& http = Http::instance(), const char* name = "http");
    const ValidatorMap& getValidators() const { return validators; }
    HttpReply* request(const HttpRequest& req) override;
    void setCachePostRequests(bool value) { cachePostRequests = value; }
    void setIgnoreHostname(bool value) { ignoreHostname = value; }
    void setMaxSeconds(uint seconds);
    void setMaxSize(uint maxSize);
private:
    QByteArray requestHash(const HttpRequest& req);

    LocalCache* cache;
    bool cachePostRequests{};
    Http& http;
    bool ignoreHostname{};

    /// Mapping is MIME -> validating function
    /// Use * as MIME to define a catch-all validator
    ValidatorMap validators;
};

class CachedHttpReply : public HttpReply
{
    Q_OBJECT
public:
    CachedHttpReply(const QByteArray& body, const QUrl& url, bool autoSignals = true);
    QByteArray body() const override { return bytes; }
    int statusCode() const override { return 200; }
    QUrl url() const override { return requestUrl; }
private:
    const QByteArray bytes;
    const QUrl requestUrl;
private slots:
    void emitSignals();
};

class WrappedHttpReply : public HttpReply
{
    Q_OBJECT
public:
    WrappedHttpReply(CachedHttp& cachedHttp, LocalCache* cache, const QByteArray& key, HttpReply* httpReply);
    QByteArray body() const override { return httpReply->body(); }
    int statusCode() const override { return httpReply->statusCode(); }
    QUrl url() const override { return httpReply->url(); }
private:
    LocalCache* cache;
    CachedHttp& cachedHttp;
    HttpReply* httpReply;
    QByteArray key;
private slots:
    void originFinished(const HttpReply& reply);
};
