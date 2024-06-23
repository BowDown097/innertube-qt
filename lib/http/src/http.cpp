#include "http.h"
#include "networkhttpreply.h"

namespace
{
    QNetworkAccessManager* networkAccessManager()
    {
        static thread_local QNetworkAccessManager* nam = [] {
            QNetworkAccessManager* nam = new QNetworkAccessManager;
    #if QT_VERSION >= QT_VERSION_CHECK(5, 9, 0)
            nam->setRedirectPolicy(QNetworkRequest::NoLessSafeRedirectPolicy);
    #endif
            return nam;
        }();
        return nam;
    }

    int defaultMaxRetries = 3;
    int defaultReadTimeout = 10000;
} // namespace

Http::Http()
    : maxRetries(defaultMaxRetries), readTimeout(defaultReadTimeout), requestHeaders(getDefaultRequestHeaders()) {}

HttpReply* Http::deleteResource(const QUrl& url)
{
    return request(HttpRequest {
        .headers = requestHeaders,
        .operation = QNetworkAccessManager::DeleteOperation,
        .url = url
    });
}

HttpReply* Http::get(const QUrl& url)
{
    return request(url, QNetworkAccessManager::GetOperation);
}

const QMap<QByteArray, QByteArray>& Http::getDefaultRequestHeaders()
{
    static const QMap<QByteArray, QByteArray> defaultRequestHeaders = [] {
        QMap<QByteArray, QByteArray> h;
        h.insert("Accept-Charset", "utf-8");
        h.insert("Connection", "Keep-Alive");
        return h;
    }();
    return defaultRequestHeaders;
}

HttpReply* Http::head(const QUrl& url)
{
    return request(url, QNetworkAccessManager::HeadOperation);
}

QNetworkReply* Http::networkReply(const HttpRequest& req)
{
    QNetworkRequest qnr(req.url);

    QMap<QByteArray, QByteArray>& headers = requestHeaders;
    if (!req.headers.isEmpty())
        headers = req.headers;

    for (auto it = headers.constBegin(); it != headers.constEnd(); ++it)
        qnr.setRawHeader(it.key(), it.value());

    if (req.offset > 0)
        qnr.setRawHeader("Range", QStringLiteral("bytes=%1-").arg(req.offset).toUtf8());

    QNetworkAccessManager* manager = networkAccessManager();
    QNetworkReply* networkReply{};

    switch (req.operation)
    {
    case QNetworkAccessManager::GetOperation:
        networkReply = manager->get(qnr);
        break;
    case QNetworkAccessManager::HeadOperation:
        networkReply = manager->head(qnr);
        break;
    case QNetworkAccessManager::PostOperation:
        networkReply = manager->post(qnr, req.body);
        break;
    case QNetworkAccessManager::PutOperation:
        networkReply = manager->put(qnr, req.body);
        break;
    case QNetworkAccessManager::DeleteOperation:
        networkReply = manager->deleteResource(qnr);
        break;
    default:
        qWarning() << "Unknown operation:" << req.operation;
    }

    return networkReply;
}

HttpReply* Http::post(const QUrl& url, const QMap<QString, QString>& params)
{
    QByteArray body;
    for (auto it = params.constBegin(); it != params.constEnd(); ++it)
        body += QUrl::toPercentEncoding(it.key()) + '=' + QUrl::toPercentEncoding(it.value()) + '&';

    HttpRequest req = {
        .body = body,
        .headers = requestHeaders,
        .operation = QNetworkAccessManager::PostOperation,
        .url = url
    };

    req.headers.insert("Content-Type", "application/x-www-form-urlencoded");
    return request(req);
}

HttpReply* Http::post(const QUrl& url, const QByteArray& body, const QByteArray& contentType)
{
    HttpRequest req = {
        .body = body,
        .headers = requestHeaders,
        .operation = QNetworkAccessManager::PostOperation,
        .url = url
    };

    req.headers.insert("Content-Type", contentType.isEmpty()
        ? QByteArray("application/x-www-form-urlencoded") : contentType);
    return request(req);
}

HttpReply* Http::put(const QUrl& url, const QByteArray& body, const QByteArray& contentType)
{
    HttpRequest req = {
        .body = body,
        .headers = requestHeaders,
        .operation = QNetworkAccessManager::PutOperation,
        .url = url
    };

    req.headers.insert("Content-Type", contentType.isEmpty()
        ? QByteArray("application/x-www-form-urlencoded") : contentType);
    return request(req);
}

HttpReply* Http::request(const HttpRequest& req)
{
    return new NetworkHttpReply(req, *this);
}

HttpReply* Http::request(const QUrl& url, QNetworkAccessManager::Operation operation, const QByteArray& body, uint offset)
{
    return request(HttpRequest {
        .body = body,
        .offset = offset,
        .operation = operation,
        .url = url
    });
}

void Http::setDefaultReadTimeout(int timeout)
{
    defaultReadTimeout = timeout;
}
