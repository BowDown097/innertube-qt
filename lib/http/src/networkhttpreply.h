#pragma once
#include "httpreply.h"
#include "httprequest.h"
#include <QNetworkReply>

class Http;
class QTimer;

class NetworkHttpReply : public HttpReply
{
    Q_OBJECT
public:
    NetworkHttpReply(const HttpRequest& req, Http& http);
    QByteArray body() const override { return bytes; }
    QByteArray header(const QByteArray& headerName) const override { return networkReply->rawHeader(headerName); }
    const QList<QNetworkReply::RawHeaderPair> headers() const override { return networkReply->rawHeaderPairs(); }
    QUrl url() const override { return networkReply->url(); }

    QString reasonPhrase() const override
    { return networkReply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString(); }
    int statusCode() const override
    { return networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(); }
private:
    void emitError();
    void emitFinished();
    QString errorMessage();
    void setupReply();

    QByteArray bytes;
    Http& http;
    QNetworkReply* networkReply;
    QTimer* readTimeoutTimer;
    HttpRequest req;
    int retryCount{};
private slots:
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void readTimeout();
    void replyError(QNetworkReply::NetworkError);
    void replyFinished();
};
