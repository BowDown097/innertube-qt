#pragma once
#include "http.h"
#include <QElapsedTimer>

class QTimer;

class ThrottledHttp : public Http
{
public:
    ThrottledHttp(Http& http = Http::instance());
    HttpReply* request(const HttpRequest& req) override;
    void setMilliseconds(int milliseconds) { this->milliseconds = milliseconds; }
private:
    QElapsedTimer elapsedTimer;
    Http& http;
    int milliseconds;
};

class ThrottledHttpReply : public HttpReply
{
    Q_OBJECT
public:
    ThrottledHttpReply(Http& http, const HttpRequest& req, int milliseconds, QElapsedTimer& elapsedTimer);
    QByteArray body() const override { return QByteArray(); }
    int statusCode() const override { return 200; }
    QUrl url() const override { return req.url; }
private slots:
    void checkElapsed();
private:
    void doRequest();
    QElapsedTimer& elapsedTimer;
    Http& http;
    int milliseconds = 1000;
    HttpRequest req;
    QTimer* timer{};
};
