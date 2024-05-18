#include "networkhttpreply.h"
#include "http.h"
#include <QTimer>

NetworkHttpReply::NetworkHttpReply(const HttpRequest& req, Http& http) : http(http), req(req)
{
    if (req.url.isEmpty())
        qWarning() << "Empty URL";

    networkReply = http.networkReply(req);
    setParent(networkReply);
    setupReply();

    readTimeoutTimer = new QTimer(this);
    readTimeoutTimer->setInterval(http.getReadTimeout());
    readTimeoutTimer->setSingleShot(true);
    readTimeoutTimer->start();
    connect(readTimeoutTimer, &QTimer::timeout, this, &NetworkHttpReply::readTimeout, Qt::UniqueConnection);
}

void NetworkHttpReply::downloadProgress(qint64 bytesReceived, qint64 /* bytesTotal */)
{
    if (bytesReceived > 0 && readTimeoutTimer->isActive())
    {
        readTimeoutTimer->stop();
        disconnect(networkReply, &QNetworkReply::downloadProgress, this, &NetworkHttpReply::downloadProgress);
    }
}

void NetworkHttpReply::emitError()
{
    const QString msg = errorMessage();
#ifdef HTTP_DEBUG
    qDebug() << "Http:" << msg;
    if (!req.body.isEmpty()) qDebug() << "Http:" << req.body;
#endif
    emit error(msg);
    emitFinished();
}

void NetworkHttpReply::emitFinished()
{
    readTimeoutTimer->stop();

    // disconnect to avoid replyFinished() from being called
    networkReply->disconnect();

    emit finished(*this);

    // bye bye my reply
    // this will also delete this object and HttpReply as the QNetworkReply is their parent
    networkReply->deleteLater();
}

QString NetworkHttpReply::errorMessage()
{
    return url().toString() + ' ' + QString::number(statusCode()) + ' ' + reasonPhrase();
}

void NetworkHttpReply::readTimeout()
{
#ifdef HTTP_DEBUG
    qDebug() << "Timeout" << req.url;
#endif

    if (!networkReply)
        return;

    bool shouldRetry = (networkReply->operation() == QNetworkAccessManager::GetOperation ||
                        networkReply->operation() == QNetworkAccessManager::HeadOperation) &&
                       retryCount < http.getMaxRetries();

    networkReply->disconnect();
    networkReply->abort();
    networkReply->deleteLater();

    if (!shouldRetry)
    {
        emitError();
        emit finished(*this);
        return;
    }

    retryCount++;
    QNetworkReply* retryReply = http.networkReply(req);
    setParent(retryReply);
    networkReply = retryReply;
    setupReply();
    readTimeoutTimer->start();
}

void NetworkHttpReply::replyFinished()
{
#if QT_VERSION < QT_VERSION_CHECK(5, 9, 0)
    if (QUrl redirect = networkReply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl(); redirect.isValid())
    {
        if (redirect.isRelative())
            redirect = networkReply->url().resolved(redirect);

# ifdef HTTP_DEBUG
        qDebug() << "Redirected to" << redirect;
# endif

        HttpRequest redirectReq {
            .body = req.body,
            .offset = req.offset,
            .operation = req.operation,
            .url = redirect
        };

        QNetworkReply* redirectReply = http.networkReply(redirectReq);
        setParent(redirectReply);
        networkReply->deleteLater();
        networkReply = redirectReply;
        setupReply();
        readTimeoutTimer->start();
        return;
    }
#endif

    if (isSuccessful())
    {
        bytes = networkReply->readAll();
        emit data(bytes);
    }

    emitFinished();
}

void NetworkHttpReply::replyError([[maybe_unused]] QNetworkReply::NetworkError code)
{
    const int status = statusCode();
    if (retryCount <= http.getMaxRetries() && status >= 500 && status < 600 &&
        (networkReply->operation() == QNetworkAccessManager::GetOperation ||
         networkReply->operation() == QNetworkAccessManager::HeadOperation))
    {
#ifdef HTTP_DEBUG
        qDebug() << "Retrying" << status << QVariant(req.operation).toString() << req.url;
#endif
        networkReply->disconnect();
        networkReply->deleteLater();
        QNetworkReply* retryReply = http.networkReply(req);
        setParent(retryReply);
        networkReply = retryReply;
        setupReply();
        retryCount++;
        readTimeoutTimer->start();
    }
    else
    {
        emitError();
        return;
    }
}

void NetworkHttpReply::setupReply()
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
    connect(networkReply, &QNetworkReply::errorOccurred, this, &NetworkHttpReply::replyError, Qt::UniqueConnection);
#else
    connect(networkReply, &QNetworkReply::error, this, &NetworkHttpReply::replyError, Qt::UniqueConnection);
#endif
    connect(networkReply, &QNetworkReply::finished, this, &NetworkHttpReply::replyFinished, Qt::UniqueConnection);
    connect(networkReply, &QNetworkReply::downloadProgress, this, &NetworkHttpReply::downloadProgress, Qt::UniqueConnection);
}
